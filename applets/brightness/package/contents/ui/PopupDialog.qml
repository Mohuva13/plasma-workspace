/*
    SPDX-FileCopyrightText: 2011 Viranch Mehta <viranch.mehta@gmail.com>
    SPDX-FileCopyrightText: 2013-2016 Kai Uwe Broulik <kde@privat.broulik.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

import QtQuick 2.15
import QtQuick.Layouts 1.15

import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.kirigami 2.20 as Kirigami

PlasmaExtras.Representation {
    id: dialog

    property bool isBrightnessAvailable
    property bool isScreenBrightnessAvailable
    property bool isKeyboardBrightnessAvailable

    contentItem: PlasmaComponents3.ScrollView {
        id: scrollView

        focus: false

        function positionViewAtItem(item) {
            if (!PlasmaComponents3.ScrollBar.vertical.visible) {
                return;
            }
            const rect = brightnessList.mapFromItem(item, 0, 0, item.width, item.height);
            if (rect.y < scrollView.contentItem.contentY) {
                scrollView.contentItem.contentY = rect.y;
            } else if (rect.y + rect.height > scrollView.contentItem.contentY + scrollView.height) {
                scrollView.contentItem.contentY = rect.y + rect.height - scrollView.height;
            }
        }

        Column {
            id: brightnessList

            spacing: Kirigami.Units.smallSpacing * 2

            readonly property Item firstHeaderItem: {
                if (brightnessSlider.visible) {
                    return brightnessSlider;
                } else if (keyboardBrightnessSlider.visible) {
                    return keyboardBrightnessSlider;
                }
                return null;
            }
            readonly property Item lastHeaderItem: {
                if (keyboardBrightnessSlider.visible) {
                    return keyboardBrightnessSlider;
                } else if (brightnessSlider.visible) {
                    return brightnessSlider;
                }
                return null;
            }

            BrightnessItem {
                id: brightnessSlider

                width: scrollView.availableWidth

                icon.name: "video-display-brightness"
                text: i18n("Display Brightness")
                type: BrightnessItem.Type.Screen
                visible: dialog.isBrightnessAvailable
                value: brightnesscontrol.screenBrightness
                maximumValue: brightnesscontrol.maximumScreenBrightness

                KeyNavigation.down: keyboardBrightnessSlider.visible ? keyboardBrightnessSlider : keyboardBrightnessSlider.KeyNavigation.down
                KeyNavigation.backtab: KeyNavigation.up
                KeyNavigation.tab: KeyNavigation.down
                stepSize: brightnesscontrol.maximumScreenBrightness/100

                onMoved: brightnesscontrol.screenBrightness = value
                onActiveFocusChanged: if (activeFocus) scrollView.positionViewAtItem(this)

                // Manually dragging the slider around breaks the binding
                Connections {
                    target: brightnesscontrol
                    function onScreenBrightnessChanged() {
                        brightnessSlider.value = brightnesscontrol.screenBrightness;
                    }
                }
            }

            BrightnessItem {
                id: keyboardBrightnessSlider

                width: scrollView.availableWidth

                icon.name: "input-keyboard-brightness"
                text: i18n("Keyboard Brightness")
                type: BrightnessItem.Type.Keyboard
                showPercentage: false
                value: brightnesscontrol.keyboardBrightness
                maximumValue: brightnesscontrol.maximumKeyboardBrightness
                visible: dialog.isKeyboardBrightnessAvailable

                KeyNavigation.up: brightnessSlider.visible ? brightnessSlider : brightnessSlider.KeyNavigation.up
                // KeyNavigation.down: powerProfileItem.visible ? powerProfileItem : powerProfileItem.KeyNavigation.down // todo
                KeyNavigation.backtab: KeyNavigation.up
                KeyNavigation.tab: KeyNavigation.down

                onMoved: brightnesscontrol.keyboardBrightness = value
                onActiveFocusChanged: if (activeFocus) scrollView.positionViewAtItem(this)

                // Manually dragging the slider around breaks the binding
                Connections {
                    target: brightnesscontrol
                    function onKeyboardBrightnessChanged() {
                        keyboardBrightnessSlider.value = brightnesscontrol.keyboardBrightness;
                    }
                }
            }

            NightColorItem {
                id: nightColorItem

                width: scrollView.availableWidth

                text: i18n("Night Color")
            }

        }
    }
}

