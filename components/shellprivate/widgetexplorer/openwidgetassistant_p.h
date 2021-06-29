/*
    SPDX-FileCopyrightText: 2008 Aaron Seigo <aseigo@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PLASMA_OPENWIDGETASSISTANT_P_H
#define PLASMA_OPENWIDGETASSISTANT_P_H

#include <KAssistantDialog>

class KFileWidget;
class QListWidget;

namespace Plasma
{
class OpenWidgetAssistant : public KAssistantDialog
{
    Q_OBJECT

public:
    explicit OpenWidgetAssistant(QWidget *parent);

protected Q_SLOTS:
    void finished();
    void slotHelpClicked();

private:
    KPageWidgetItem *m_filePage;
    KFileWidget *m_fileWidget;
    QWidget *m_filePageWidget;
};

} // Plasma namespace

#endif
