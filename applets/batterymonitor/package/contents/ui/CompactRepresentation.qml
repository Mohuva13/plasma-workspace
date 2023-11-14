/*
    SPDX-FileCopyrightText: 2011 Sebastian Kügler <sebas@kde.org>
    SPDX-FileCopyrightText: 2011 Viranch Mehta <viranch.mehta@gmail.com>
    SPDX-FileCopyrightText: 2013 Kai Uwe Broulik <kde@privat.broulik.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

import QtQuick 2.15
import QtQuick.Layouts 1.15

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.workspace.components 2.0 as WorkspaceComponents
import org.kde.kirigami 2.20 as Kirigami

MouseArea {
    id: root

    property real itemSize: Math.min(root.height, root.width/view.count)
    readonly property bool isConstrained: Plasmoid.formFactor === PlasmaCore.Types.Vertical || Plasmoid.formFactor === PlasmaCore.Types.Horizontal
    property real brightnessError: 0
    property QtObject batteries
    property bool hasBatteries: false
    required property bool isHeldOnPerformanceMode
    required property bool isHeldOnPowerSaveMode
    required property bool isInhibited
    required property bool isSomehowFullyCharged

    activeFocusOnTab: true
    hoverEnabled: true

    property bool wasExpanded

    Accessible.name: Plasmoid.title
    Accessible.description: `${toolTipMainText}; ${toolTipSubText}`
    Accessible.role: Accessible.Button

    onPressed: wasExpanded = batterymonitor.expanded
    onClicked: batterymonitor.expanded = !wasExpanded

    // "No Batteries" case
    Kirigami.Icon {
        anchors.fill: parent
        visible: !root.hasBatteries
        source: Plasmoid.icon
        active: root.containsMouse
    }

    // We have any batteries; show their status
    //Should we consider turning this into a Flow item?
    Row {
        visible: root.hasBatteries
        anchors.centerIn: parent
        Repeater {
            id: view

            model: root.isConstrained ? 1 : root.batteries

            Item {
                id: batteryContainer

                property int percent: root.isConstrained ? pmSource.data["Battery"]["Percent"] : model["Percent"]
                property bool pluggedIn: pmSource.data["AC Adapter"] && pmSource.data["AC Adapter"]["Plugged in"] && (root.isConstrained || model["Is Power Supply"])

                height: root.itemSize
                width: root.width/view.count

                property real iconSize: Math.min(width, height)

                // "Held on a Power Profile mode or active inhibitions while plugged in" use case; show the
                // icon of the active mode so the user can notice this at a glance
                Kirigami.Icon {
                    id: powerProfileModeIcon

                    anchors.fill: parent

                    visible: batteryContainer.pluggedIn && (root.isHeldOnPowerSaveMode || root.isHeldOnPerformanceMode || root.isInhibited)
                    source: root.isHeldOnPerformanceMode
                        ? "battery-profile-performance-symbolic"
                        : root.isHeldOnPowerSaveMode 
                        ? "battery-profile-powersave-symbolic"
                        : "speedometer-symbolic"
                    active: root.containsMouse
                }

                // Show normal battery icon
                WorkspaceComponents.BatteryIcon {
                    id: batteryIcon

                    anchors.centerIn: parent
                    height: batteryContainer.iconSize
                    width: height

                    active: root.containsMouse
                    visible: !powerProfileModeIcon.visible
                    hasBattery: root.hasBatteries
                    percent: batteryContainer.percent
                    pluggedIn: batteryContainer.pluggedIn
                }

                WorkspaceComponents.BadgeOverlay {
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right

                    visible: Plasmoid.configuration.showPercentage && !root.isSomehowFullyCharged

                    text: i18nc("battery percentage below battery icon", "%1%", percent)
                    icon: batteryIcon
                }
            }
        }
    }
}
