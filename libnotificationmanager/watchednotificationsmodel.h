/*
    SPDX-FileCopyrightText: 2020 Shah Bhushan <bshah@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef WATCHEDNOTIFICATIONSMODEL_H
#define WATCHEDNOTIFICATIONSMODEL_H

#include "abstractnotificationsmodel.h"

#include "notificationmanager_export.h"

namespace NotificationManager
{
class NOTIFICATIONMANAGER_EXPORT WatchedNotificationsModel : public AbstractNotificationsModel
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)

public:
    explicit WatchedNotificationsModel();
    ~WatchedNotificationsModel();

    Q_INVOKABLE void expire(uint notificationId) override;
    Q_INVOKABLE void close(uint notificationId) override;

    Q_INVOKABLE void invokeDefaultAction(uint notificationId) override;
    Q_INVOKABLE void invokeAction(uint notificationId, const QString &actionName) override;
    Q_INVOKABLE void reply(uint notificationId, const QString &text) override;
    bool valid();

Q_SIGNALS:
    void validChanged(bool valid);

private:
    class Private;
    Private *const d;
    Q_DISABLE_COPY(WatchedNotificationsModel)
};

}

#endif // WATCHEDNOTIFICATIONSMODEL_H
