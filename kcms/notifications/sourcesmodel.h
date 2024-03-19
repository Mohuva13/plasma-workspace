/*
    SPDX-FileCopyrightText: 2019 Kai Uwe Broulik <kde@privat.broulik.de>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include <QAbstractItemModel>
#include <QHash>
#include <QList>
#include <QString>

#include <KService>

#include "eventsettings.h"

// FIXME add constructors for KConfigGroup
struct SourceData {
    static SourceData fromService(KService::Ptr service);

    QString name;
    QString comment;
    QString iconName;
    bool isDefault = true;

    QString notifyRcName;
    QString desktopEntry;

    QList<NotificationManager::EventSettings *> events;

    QString display() const
    {
        return !name.isEmpty() ? name : comment;
    }
};

class SourcesModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SourcesModel(QObject *parent = nullptr);
    ~SourcesModel() override;

    enum Roles {
        SourceTypeRole = Qt::UserRole + 1,
        NotifyRcNameRole,
        DesktopEntryRole,
        IsDefaultRole,

        EventIdRole,
        CommentRole,
        ShowIconsRole,
        ActionsRole,
        SoundRole,
        DefaultActionsRole,
        DefaultSoundRole,
    };
    Q_ENUM(Roles)

    enum Type {
        ApplicationType,
        ServiceType,
    };
    Q_ENUM(Type)

    Q_INVOKABLE QPersistentModelIndex makePersistentModelIndex(const QModelIndex &idx) const;

    Q_INVOKABLE QPersistentModelIndex persistentIndexForDesktopEntry(const QString &desktopEntry) const;
    Q_INVOKABLE QPersistentModelIndex persistentIndexForNotifyRcName(const QString &notifyRcName) const;

    Q_INVOKABLE QPersistentModelIndex indexOfEvent(const QModelIndex &parent, const QString &eventId) const;

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void load();

    void loadEvents();
    void saveEvents();

    bool isEventSaveNeeded() const;
    bool isEventDefaults() const;
    void setEventDefaults();

private:
    QList<SourceData> m_data;
};
