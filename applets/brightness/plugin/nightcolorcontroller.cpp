/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "nightcolorcontroller.h"
#include "nightcolorcontroller_p.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>

static const QString s_serviceName = QStringLiteral("org.kde.KWin.NightLight");
static const QString s_nightColorPath = QStringLiteral("/org/kde/KWin/NightLight");
static const QString s_nightColorInterface = QStringLiteral("org.kde.KWin.NightLight");
static const QString s_propertiesInterface = QStringLiteral("org.freedesktop.DBus.Properties");

NightColorControllerPrivate::NightColorControllerPrivate(QObject *parent)
    : QObject(parent)
{
    QDBusConnection bus = QDBusConnection::sessionBus();

    // clang-format off
    const bool connected = bus.connect(s_serviceName,
                                       s_nightColorPath,
                                       s_propertiesInterface,
                                       QStringLiteral("PropertiesChanged"),
                                       this,
                                       SLOT(handlePropertiesChanged(QString,QVariantMap,QStringList)));
    // clang-format on
    if (!connected) {
        return;
    }

    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_nightColorPath, s_propertiesInterface, QStringLiteral("GetAll"));
    message.setArguments({s_nightColorInterface});

    QDBusPendingReply<QVariantMap> properties = bus.asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(properties, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *self) {
        self->deleteLater();

        const QDBusPendingReply<QVariantMap> properties = *self;
        if (properties.isError()) {
            return;
        }

        updateProperties(properties.value());
    });
}

NightColorControllerPrivate::~NightColorControllerPrivate()
{
}

void NightColorControllerPrivate::handlePropertiesChanged(const QString &interfaceName,
                                                          const QVariantMap &changedProperties,
                                                          const QStringList &invalidatedProperties)
{
    Q_UNUSED(interfaceName)
    Q_UNUSED(invalidatedProperties)

    updateProperties(changedProperties);
}

int NightColorControllerPrivate::currentTemperature() const
{
    return m_currentTemperature;
}

int NightColorControllerPrivate::targetTemperature() const
{
    return m_targetTemperature;
}

void NightColorControllerPrivate::updateProperties(const QVariantMap &properties)
{
    const QVariant available = properties.value(QStringLiteral("available"));
    if (available.isValid()) {
        setAvailable(available.toBool());
    }

    const QVariant enabled = properties.value(QStringLiteral("enabled"));
    if (enabled.isValid()) {
        setEnabled(enabled.toBool());
    }

    const QVariant running = properties.value(QStringLiteral("running"));
    if (running.isValid()) {
        setRunning(running.toBool());
    }

    const QVariant mode = properties.value(QStringLiteral("mode"));
    if (mode.isValid()) {
        setMode(mode.toInt());
    }

    const QVariant daylight = properties.value(QStringLiteral("daylight"));
    if (daylight.isValid()) {
        setDaylight(daylight.toBool());
    }

    const QVariant currentTemperature = properties.value(QStringLiteral("currentTemperature"));
    if (currentTemperature.isValid()) {
        setCurrentTemperature(currentTemperature.toInt());
    }

    const QVariant targetTemperature = properties.value(QStringLiteral("targetTemperature"));
    if (targetTemperature.isValid()) {
        setTargetTemperature(targetTemperature.toInt());
    }

    const QVariant currentTransitionStartTime = properties.value(QStringLiteral("previousTransitionDateTime"));
    const QVariant currentTransitionDuration = properties.value(QStringLiteral("previousTransitionDuration"));
    if (currentTransitionStartTime.isValid() && currentTransitionDuration.isValid()) {
        setCurrentTransitionEndTime(currentTransitionStartTime.toULongLong() * 1000 + currentTransitionDuration.toUInt());
    }

    const QVariant scheduledTransitionStartTime = properties.value(QStringLiteral("scheduledTransitionDateTime"));
    if (scheduledTransitionStartTime.isValid()) {
        setScheduledTransitionStartTime(scheduledTransitionStartTime.toULongLong() * 1000);
    }
}

void NightColorControllerPrivate::setCurrentTemperature(int temperature)
{
    if (m_currentTemperature == temperature) {
        return;
    }
    m_currentTemperature = temperature;
    Q_EMIT currentTemperatureChanged();
}

void NightColorControllerPrivate::setTargetTemperature(int temperature)
{
    if (m_targetTemperature == temperature) {
        return;
    }
    m_targetTemperature = temperature;
    Q_EMIT targetTemperatureChanged();
}

bool NightColorControllerPrivate::isAvailable() const
{
    return m_isAvailable;
}

void NightColorControllerPrivate::setAvailable(bool available)
{
    if (m_isAvailable == available) {
        return;
    }
    m_isAvailable = available;
    Q_EMIT availableChanged();
}

bool NightColorControllerPrivate::isEnabled() const
{
    return m_isEnabled;
}

void NightColorControllerPrivate::setEnabled(bool enabled)
{
    if (m_isEnabled == enabled) {
        return;
    }
    m_isEnabled = enabled;
    Q_EMIT enabledChanged();
}

bool NightColorControllerPrivate::isRunning() const
{
    return m_isRunning;
}

void NightColorControllerPrivate::setRunning(bool running)
{
    if (m_isRunning == running) {
        return;
    }
    m_isRunning = running;
    Q_EMIT runningChanged();
}

int NightColorControllerPrivate::mode() const
{
    return m_mode;
}

void NightColorControllerPrivate::setMode(int mode)
{
    if (m_mode == mode) {
        return;
    }
    m_mode = mode;
    Q_EMIT modeChanged();
}

bool NightColorControllerPrivate::isDaylight() const
{
    return m_isDaylight;
}

void NightColorControllerPrivate::setDaylight(bool daylight)
{
    if (m_isDaylight == daylight) {
        return;
    }
    m_isDaylight = daylight;
    Q_EMIT daylightChanged();
}

quint64 NightColorControllerPrivate::currentTransitionEndTime() const
{
    return m_currentTransitionEndTime;
}

void NightColorControllerPrivate::setCurrentTransitionEndTime(quint64 currentTransitionEndTime)
{
    if (m_currentTransitionEndTime == currentTransitionEndTime) {
        return;
    }
    m_currentTransitionEndTime = currentTransitionEndTime;
    Q_EMIT currentTransitionEndTimeChanged();
}

quint64 NightColorControllerPrivate::scheduledTransitionStartTime() const
{
    return m_scheduledTransitionStartTime;
}

void NightColorControllerPrivate::setScheduledTransitionStartTime(quint64 scheduledTransitionStartTime)
{
    if (m_scheduledTransitionStartTime == scheduledTransitionStartTime) {
        return;
    }
    m_scheduledTransitionStartTime = scheduledTransitionStartTime;
    Q_EMIT scheduledTransitionStartTimeChanged();
}

NightColorController::InhibitionState NightColorControllerPrivate::inhibitionState() const
{
    return m_inhibitionState;
}

void NightColorController::inhibit()
{
    if (d->state == Inhibited) {
        return;
    }

    d->pendingUninhibit = false;

    if (d->state == Inhibiting) {
        return;
    }

    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_path, s_interface, QStringLiteral("inhibit"));

    QDBusPendingReply<uint> cookie = QDBusConnection::sessionBus().asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(cookie, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *self) {
        const bool wasPendingUninhibit = d->pendingUninhibit;
        d->pendingUninhibit = false;

        const QDBusPendingReply<uint> reply = *self;
        self->deleteLater();

        if (reply.isError()) {
            qCWarning(NIGHTCOLOR_CONTROL()) << "Could not inhibit Night Color:" << reply.error().message();
            d->state = Uninhibited;
            Q_EMIT stateChanged();
            return;
        }

        d->cookie = reply.value();
        d->state = Inhibited;
        Q_EMIT stateChanged();

        if (wasPendingUninhibit) {
            uninhibit();
        }
    });

    d->state = Inhibiting;
    Q_EMIT stateChanged();
}

void NightColorInhibitor::uninhibit()
{
    if (d->state == Uninhibiting || d->state == Uninhibited) {
        return;
    }

    if (d->state == Inhibiting) {
        d->pendingUninhibit = true;
        return;
    }

    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_path, s_interface, QStringLiteral("uninhibit"));
    message.setArguments({d->cookie});

    QDBusPendingReply<void> reply = QDBusConnection::sessionBus().asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *self) {
        self->deleteLater();

        if (d->state != Uninhibiting) {
            return;
        }

        const QDBusPendingReply<void> reply = *self;
        if (reply.isError()) {
            qCWarning(NIGHTCOLOR_CONTROL) << "Could not uninhibit Night Color:" << reply.error().message();
        }

        d->state = Uninhibited;
        Q_EMIT stateChanged();
    });

    d->state = Uninhibiting;
    Q_EMIT stateChanged();
}

NightColorController::NightColorController(QObject *parent)
    : QObject(parent)
    , d(new NightColorControllerPrivate(this))
{
    connect(d, &NightColorControllerPrivate::availableChanged, this, &NightColorController::availableChanged);
    connect(d, &NightColorControllerPrivate::enabledChanged, this, &NightColorController::enabledChanged);
    connect(d, &NightColorControllerPrivate::runningChanged, this, &NightColorController::runningChanged);
    connect(d, &NightColorControllerPrivate::modeChanged, this, &NightColorController::modeChanged);
    connect(d, &NightColorControllerPrivate::daylightChanged, this, &NightColorController::daylightChanged);
    connect(d, &NightColorControllerPrivate::currentTransitionEndTimeChanged, this, &NightColorController::currentTransitionEndTimeChanged);
    connect(d, &NightColorControllerPrivate::scheduledTransitionStartTimeChanged, this, &NightColorController::scheduledTransitionStartTimeChanged);
    connect(d, &NightColorControllerPrivate::currentTemperatureChanged, this, &NightColorController::currentTemperatureChanged);
    connect(d, &NightColorControllerPrivate::targetTemperatureChanged, this, &NightColorController::targetTemperatureChanged);
}

NightColorController::~NightColorController()
{
}

bool NightColorController::isAvailable() const
{
    return d->isAvailable();
}

bool NightColorController::isEnabled() const
{
    return d->isEnabled();
}

bool NightColorController::isRunning() const
{
    return d->isRunning();
}

int NightColorController::mode() const
{
    return d->mode();
}

bool NightColorController::isDaylight() const
{
    return d->isDaylight();
}

int NightColorController::currentTemperature() const
{
    return d->currentTemperature();
}

int NightColorController::targetTemperature() const
{
    return d->targetTemperature();
}

quint64 NightColorController::currentTransitionEndTime() const
{
    return d->currentTransitionEndTime();
}

quint64 NightColorController::scheduledTransitionStartTime() const
{
    return d->scheduledTransitionStartTime();
}

NightColorController::InhibitionState NightColorController::inhibitionState() const
{
    return d->inhibitionState();
}

#include "moc_nightcolorcontroller.cpp"
