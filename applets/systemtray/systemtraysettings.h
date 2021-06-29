/*
    SPDX-FileCopyrightText: 2020 Konrad Materka <materka@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SYSTEMTRAYSETTINGS_H
#define SYSTEMTRAYSETTINGS_H

#include <QObject>
#include <QPointer>
#include <QStringList>

class KConfigLoader;

/**
 * @brief The SystemTraySettings class
 */
class SystemTraySettings : public QObject
{
    Q_OBJECT
public:
    explicit SystemTraySettings(KConfigLoader *config, QObject *parent = nullptr);

    virtual bool isKnownPlugin(const QString &pluginId);
    virtual const QStringList knownPlugins() const;
    virtual void addKnownPlugin(const QString &pluginId);
    virtual void removeKnownPlugin(const QString &pluginId);

    virtual bool isEnabledPlugin(const QString &pluginId) const;
    virtual const QStringList enabledPlugins() const;
    virtual void addEnabledPlugin(const QString &pluginId);
    virtual void removeEnabledPlugin(const QString &pluginId);

    virtual bool isShowAllItems() const;
    virtual const QStringList shownItems() const;
    virtual const QStringList hiddenItems() const;

    virtual void cleanupPlugin(const QString &pluginId);

Q_SIGNALS:
    void configurationChanged();
    void enabledPluginsChanged(const QStringList &enabledPlugins, const QStringList &disabledPlugins);

private:
    void loadConfig();
    void writeConfigValue(const QString &key, const QVariant &value);
    void notifyAboutChangedEnabledPlugins(const QStringList &enabledPluginsOld, const QStringList &enabledPluginsNew);

    QPointer<KConfigLoader> config;

    bool updatingConfigValue = false;
    QStringList m_extraItems;
    QStringList m_knownItems;
};

#endif // SYSTEMTRAYSETTINGS_H
