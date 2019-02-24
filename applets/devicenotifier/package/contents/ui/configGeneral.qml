/*
 *  Copyright 2013 Bhushan Shah <bhush94@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  2.010-1301, USA.
 */

import QtQuick 2.0
import QtQuick.Controls 2.5
import org.kde.kirigami 2.4 as Kirigami

Item {
    width: childrenRect.width
    height: childrenRect.height

    property alias cfg_removableDevices: removableOnly.checked
    property alias cfg_nonRemovableDevices: nonRemovableOnly.checked
    property alias cfg_allDevices: allDevices.checked
    property alias cfg_popupOnNewDevice: autoPopup.checked

    Kirigami.FormLayout {
        anchors.left: parent.left
        anchors.right: parent.right

        RadioButton {
            id: removableOnly
            Kirigami.FormData.label: i18n("Show:")
            text: i18n("Removable devices only")
        }

        RadioButton {
            id: nonRemovableOnly
            text: i18n("Non-removable devices only")
        }

        RadioButton {
            id: allDevices
            text: i18n("All devices")
        }

        CheckBox {
            id: autoPopup
            text: i18n("Open popup when new device is plugged in")
        }
    }
}
