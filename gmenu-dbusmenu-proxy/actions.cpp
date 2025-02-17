/*
    SPDX-FileCopyrightText: 2018 Kai Uwe Broulik <kde@privat.broulik.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "actions.h"

#include "debug.h"

#include <QDBusConnection>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDebug>

Actions::Actions(const QString &serviceName, const QString &objectPath, QObject *parent)
    : QObject(parent)
    , m_interface(new OrgGtkActionsInterface(serviceName, objectPath, QDBusConnection::sessionBus(), this))
{
    connect(m_interface.get(), &OrgGtkActionsInterface::Changed, this, &Actions::onActionsChanged);
}

Actions::~Actions() = default;

void Actions::load()
{
    QDBusPendingReply<GMenuActionMap> reply = m_interface->DescribeAll();
    auto *watcher = new QDBusPendingCallWatcher(reply, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<GMenuActionMap> reply = *watcher;
        if (reply.isError()) {
            qCWarning(DBUSMENUPROXY) << "Failed to get actions from" << m_interface->service() << "at" << m_interface->path() << reply.error();
            Q_EMIT failedToLoad();
        } else {
            m_actions = reply.value();
            Q_EMIT loaded();
        }
        watcher->deleteLater();
    });
}

bool Actions::get(const QString &name, GMenuAction &action) const
{
    auto it = m_actions.find(name);
    if (it == m_actions.constEnd()) {
        return false;
    }

    action = *it;
    return true;
}

GMenuActionMap Actions::getAll() const
{
    return m_actions;
}

void Actions::trigger(const QString &name, const QVariant &target, uint timestamp)
{
    if (!m_actions.contains(name)) {
        qCWarning(DBUSMENUPROXY) << "Cannot invoke action" << name << "which doesn't exist";
        return;
    }

    QVariantList parameter;
    if (target.isValid()) {
        parameter << target;
    }

    QVariantMap platformData;
    if (timestamp) {
        // From documentation:
        // If the startup notification id is not available, this can be just "_TIMEtime", where
        // time is the time stamp from the event triggering the call.
        // see also gtkwindow.c extract_time_from_startup_id and startup_id_is_fake
        platformData.insert(QStringLiteral("desktop-startup-id"), QStringLiteral("_TIME") + QString::number(timestamp));
    }

    QDBusPendingReply<void> reply = m_interface->Activate(name, parameter, platformData);
    auto *watcher = new QDBusPendingCallWatcher(reply, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, name](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<void> reply = *watcher;
        if (reply.isError()) {
            qCWarning(DBUSMENUPROXY) << "Failed to invoke action" << name << "on" << m_interface->service() << "at" << m_interface->path() << reply.error();
        }
        watcher->deleteLater();
    });
}

bool Actions::isValid() const
{
    return !m_actions.isEmpty();
}

void Actions::onActionsChanged(const QStringList &removed, const StringBoolMap &enabledChanges, const QVariantMap &stateChanges, const GMenuActionMap &added)
{
    // Collect the actions that we removed, altered, or added, so we can eventually signal changes for all menus that contain one of those actions
    QStringList dirtyActions;

    // TODO I bet for most of the loops below we could use a nice short std algorithm

    for (const QString &removedAction : removed) {
        if (m_actions.remove(removedAction)) {
            dirtyActions.append(removedAction);
        }
    }

    for (auto it = enabledChanges.constBegin(), end = enabledChanges.constEnd(); it != end; ++it) {
        const QString &actionName = it.key();
        const bool enabled = it.value();

        auto actionIt = m_actions.find(actionName);
        if (actionIt == m_actions.end()) {
            qCInfo(DBUSMENUPROXY) << "Got enabled changed for action" << actionName << "which we don't know";
            continue;
        }

        GMenuAction &action = *actionIt;
        if (action.enabled != enabled) {
            action.enabled = enabled;
            dirtyActions.append(actionName);
        } else {
            qCInfo(DBUSMENUPROXY) << "Got enabled change for action" << actionName << "which didn't change it";
        }
    }

    for (auto it = stateChanges.constBegin(), end = stateChanges.constEnd(); it != end; ++it) {
        const QString &actionName = it.key();
        const QVariant &state = it.value();

        auto actionIt = m_actions.find(actionName);
        if (actionIt == m_actions.end()) {
            qCInfo(DBUSMENUPROXY) << "Got state changed for action" << actionName << "which we don't know";
            continue;
        }

        GMenuAction &action = *actionIt;

        if (action.state.isEmpty()) {
            qCDebug(DBUSMENUPROXY) << "Got new state for action" << actionName << "that didn't have any state before";
            action.state.append(state);
            dirtyActions.append(actionName);
        } else {
            // Action state is a list but the state change only sends us a single variant, so just overwrite the first one
            QVariant &firstState = action.state.first();
            if (firstState != state) {
                firstState = state;
                dirtyActions.append(actionName);
            } else {
                qCInfo(DBUSMENUPROXY) << "Got state change for action" << actionName << "which didn't change it";
            }
        }
    }

    // unite() will result in keys being present multiple times, do it manually and overwrite existing ones
    for (auto it = added.constBegin(), end = added.constEnd(); it != end; ++it) {
        const QString &actionName = it.key();

        if (DBUSMENUPROXY().isInfoEnabled()) {
            if (m_actions.contains(actionName)) {
                qCInfo(DBUSMENUPROXY) << "Got new action" << actionName << "that we already have, overwriting existing one";
            }
        }

        m_actions.insert(actionName, it.value());

        dirtyActions.append(actionName);
    }

    if (!dirtyActions.isEmpty()) {
        Q_EMIT actionsChanged(dirtyActions);
    }
}
