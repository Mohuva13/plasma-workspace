/* This file is part of the KDE project
    Copyright (C) by Andrew Stanley-Jones <asj@cban.com>
    SPDX-FileCopyrightText: 2004 Esben Mose Hansen <kde@mosehansen.dk>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef TRAY_H
#define TRAY_H

#include <KStatusNotifierItem>

class Klipper;

class KlipperTray : public KStatusNotifierItem
{
    Q_OBJECT

public:
    KlipperTray();

public Q_SLOTS:
    void slotSetToolTipFromHistory();

private:
    Klipper *m_klipper;
};

#endif
