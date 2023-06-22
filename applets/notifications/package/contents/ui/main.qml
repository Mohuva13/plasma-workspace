/*
    SPDX-FileCopyrightText: 2018-2019 Kai Uwe Broulik <kde@privat.broulik.de>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.8
import QtQml 2.15

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kquickcontrolsaddons 2.0 // For KCMShell

import org.kde.coreaddons 1.0 as KCoreAddons
import org.kde.kcmutils as KCMUtils
import org.kde.config as KConfig

import org.kde.notificationmanager 1.0 as NotificationManager

import org.kde.plasma.private.notifications 2.0 as Notifications

import "global"

PlasmoidItem {
    id: root

    readonly property int effectiveStatus: historyModel.activeJobsCount > 0
                     || historyModel.unreadNotificationsCount > 0
                     || Globals.inhibited ? PlasmaCore.Types.ActiveStatus
                                          : PlasmaCore.Types.PassiveStatus
    onEffectiveStatusChanged: {
        if (effectiveStatus === PlasmaCore.Types.PassiveStatus) {
            // HACK System Tray only lets applets self-hide when in Active state
            // When we clear the notifications, the status is updated right away
            // as a result of model signals, and when we then try to collapse
            // the popup isn't hidden.
            Qt.callLater(function() {
                Plasmoid.status = effectiveStatus;
            });
        } else {
            Plasmoid.status = effectiveStatus;
        }
    }

    Plasmoid.status: effectiveStatus

    toolTipSubText: {
        var lines = [];

        if (jobAggregator.count > 0) {
            let description = i18np("%1 running job", "%1 running jobs", jobAggregator.count);

            if (jobAggregator.summary) {
                if (jobAggregator.percentage > 0) {
                    description = i18nc("Job title (percentage)", "%1 (%2%)", jobAggregator.summary, jobAggregator.percentage);
                } else {
                    description = jobAggregator.summary;
                }
            } else if (jobAggregator.percentage > 0) {
                description = i18np("%1 running job (%2%)", "%1 running jobs (%2%)", jobAggregator.count, jobAggregator.percentage);
            }

            lines.push(description);
        }

        if (!NotificationManager.Server.valid) {
            lines.push(i18n("Notification service not available"));
        } else {
            // Any notification that is newer than "lastRead" is "unread"
            // since it doesn't know the popup is on screen which makes the user see it
            var actualUnread = historyModel.unreadNotificationsCount - Globals.popupNotificationsModel.activeNotificationsCount;
            if (actualUnread > 0) {
                lines.push(i18np("%1 unread notification", "%1 unread notifications", actualUnread));
            }

            if (Globals.inhibited) {
                var inhibitedUntil = notificationSettings.notificationsInhibitedUntil
                var inhibitedUntilTime = inhibitedUntil.getTime();
                var inhibitedUntilValid = !isNaN(inhibitedUntilTime);
                var dateNow = Date.now();

                // Show until time if valid but not if too far in the future
                // TODO check app inhibition, too
                if (inhibitedUntilValid && inhibitedUntilTime - dateNow > 0
                        && inhibitedUntilTime - dateNow < 100 * 24 * 60 * 60 * 1000 /* 100 days*/) {
                        lines.push(i18n("Do not disturb until %1; middle-click to exit now",
                                     KCoreAddons.Format.formatRelativeDateTime(inhibitedUntil, Locale.ShortFormat)));
                } else {
                    lines.push(i18n("Do not disturb mode active; middle-click to exit"));
                }
            } else {
                if (lines.length === 0) {
                    lines.push(i18n("No unread notifications"));
                }
                lines.push(i18n("Middle-click to enter do not disturb mode"));
            }
        }

        return lines.join("\n");
    }

    switchWidth: PlasmaCore.Units.gridUnit * 14
    // This is to let the plasmoid expand in a vertical panel for a "sidebar" notification panel
    // The CompactRepresentation size is limited to not have the notification icon grow gigantic
    // but it should still switch over to full rep once there's enough width (disregarding the limited height)
    switchHeight: Plasmoid.formFactor === PlasmaCore.Types.Vertical ? 1 : PlasmaCore.Units.gridUnit * 10

    onExpandedChanged: expanded => {
        if (!expanded) {
            historyModel.lastRead = undefined; // reset to now
            historyModel.collapseAllGroups();
        }
    }

    compactRepresentation: CompactRepresentation {
        activeCount: Globals.popupNotificationsModel.activeNotificationsCount
        unreadCount: Math.min(99, historyModel.unreadNotificationsCount)

        jobsCount: historyModel.activeJobsCount
        jobsPercentage: historyModel.jobsPercentage

        inhibited: Globals.inhibited || !NotificationManager.Server.valid
    }

    fullRepresentation: FullRepresentation {

    }

    NotificationManager.Settings {
        id: notificationSettings
    }

    NotificationManager.Notifications {
        id: historyModel
        showExpired: true
        showDismissed: true
        showJobs: notificationSettings.jobsInNotifications
        sortMode: NotificationManager.Notifications.SortByDate
        groupMode: NotificationManager.Notifications.GroupApplicationsFlat
        groupLimit: 2
        expandUnread: true
        blacklistedDesktopEntries: notificationSettings.historyBlacklistedApplications
        blacklistedNotifyRcNames: notificationSettings.historyBlacklistedServices
        urgencies: {
            var urgencies = NotificationManager.Notifications.CriticalUrgency
                          | NotificationManager.Notifications.NormalUrgency;
            if (notificationSettings.lowPriorityHistory) {
                urgencies |= NotificationManager.Notifications.LowUrgency;
            }
            return urgencies;
        }

        onCountChanged: count => {
            if (count === 0) {
                closePlasmoid();
            }
        }
    }

    Notifications.JobAggregator {
        id: jobAggregator
        sourceModel: NotificationManager.Notifications {
            id: jobAggregatorModel
            showExpired: historyModel.showExpired
            showDismissed: historyModel.showDismissed
            showJobs: historyModel.showJobs
            showNotifications: false
            blacklistedDesktopEntries: historyModel.blacklistedDesktopEntries
            blacklistedNotifyRcNames: historyModel.blacklistedNotifyRcNames
            urgencies: historyModel.urgencies
        }
    }

    function closePlasmoid() {
        if (root.hideOnWindowDeactivate) {
            root.expanded = false;
        }
    }

    function action_clearHistory() {
        historyModel.clear(NotificationManager.Notifications.ClearExpired);
        if (historyModel.count === 0) {
            closePlasmoid();
        }
    }

    function action_configure() {
        KCMUtils.KCMLauncher.openSystemSettings("kcm_notifications");
    }

    Component.onCompleted: {
        // Use Plasmoid because Plasmoid will become an object in QML after it's deleted, while
        // Plasmoid will become null.
        Globals.adopt(root);

        Plasmoid.setAction("clearHistory", i18n("Clear All Notifications"), "edit-clear-history");
        var clearAction = Plasmoid.action("clearHistory");
        clearAction.visible = Qt.binding(function() {
            return historyModel.expiredNotificationsCount > 0;
        });

        // The applet's config window has nothing in it, so let's make the header's
        // "Configure" button open the KCM instead, like we do in the Bluetooth
        // and Networks applets
        Plasmoid.removeAction("configure");
        Plasmoid.setAction("configure", i18n("&Configure Event Notifications and Actions…"), "configure");
        Plasmoid.action("configure").visible = KConfig.KAuthorized.authorizeControlModules("kcm_notifications");
    }
}
