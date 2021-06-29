/*
    SPDX-FileCopyrightText: 2014 Martin Yrjölä <martin.yrjola@gmail.com>

    SPDX-License-Identifier: MIT
*/

#ifndef KEYBOARDLAYOUTPLUGIN_H
#define KEYBOARDLAYOUTPLUGIN_H

#include <QQmlExtensionPlugin>

class KeyboardLayoutPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri) override;
};

#endif // KEYBOARDLAYOUTPLUGIN_H
