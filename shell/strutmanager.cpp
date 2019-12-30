#include "strutmanager.h"
#include "shellcorona.h"
#include "screenpool.h"

#include <QDBusMetaType>
#include <QDBusConnection>
#include <QDBusServiceWatcher>
#include <QDBusConnectionInterface>

StrutManager::StrutManager(ShellCorona *plasmashellCorona) : QObject(plasmashellCorona),
    m_plasmashellCorona(plasmashellCorona),
    m_serviceWatcher(new QDBusServiceWatcher(this))
{
    qDBusRegisterMetaType<QList<QRect>>();

    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerObject("/StrutManager", this, QDBusConnection::ExportAllSlots);
    m_serviceWatcher->setConnection(dbus);

    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered, [=](const QString &service) {
        m_availableScreenRects.remove(service);
        m_availableScreenRegions.remove(service);
        m_serviceWatcher->removeWatchedService(service);

        emit m_plasmashellCorona->availableScreenRectChanged();
    });
}

QRect StrutManager::availableScreenRect(int id) const
{
    QRect r = m_plasmashellCorona->_availableScreenRect(id);
    QHash<int, QRect> service;
    foreach (service, m_availableScreenRects) {
        if (!service.value(id).isNull()) {
            r &= service[id];
        }
    }
    return r;
}

QRegion StrutManager::availableScreenRegion(int id) const
{
    QRegion r = m_plasmashellCorona->_availableScreenRegion(id);
    QHash<int, QRegion> service;
    foreach (service, m_availableScreenRegions) {
        if (!service.value(id).isNull()) {
            r &= service[id];
        }
    }
    return r;
}

void StrutManager::setAvailableScreenRect(const QString &service, const QString &screenName, const QRect &rect) {
    int id = m_plasmashellCorona->screenPool()->id(screenName);
    if (id == -1 || m_availableScreenRects.value(service).value(id) == rect || !addWatchedService(service)) {
        return;
    }
    m_availableScreenRects[service][id] = rect;
    emit m_plasmashellCorona->availableScreenRectChanged();
}

void StrutManager::setAvailableScreenRegion(const QString &service, const QString &screenName, const QList<QRect> &rects) {
    int id = m_plasmashellCorona->screenPool()->id(screenName);
    QRegion region;
    foreach(QRect rect, rects) {
        region += rect;
    }

    if (id == -1 || m_availableScreenRegions.value(service).value(id) == region || !addWatchedService(service)) {
        return;
    }
    m_availableScreenRegions[service][id] = region;
    emit m_plasmashellCorona->availableScreenRegionChanged();
}

bool StrutManager::addWatchedService(const QString &service) {
    if (!m_serviceWatcher->watchedServices().contains(service)) {
        if (!QDBusConnection::sessionBus().interface()->isServiceRegistered(service)) {
            return false;
        }
        m_serviceWatcher->addWatchedService(service);
    }
    return true;
}
