/*
    SPDX-FileCopyrightText: 2020 Cyril Rossi <cyril.rossi@enioka.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "componentchooserdata.h"

#include "componentchooserbrowser.h"
#include "componentchooseremail.h"
#include "componentchooserfilemanager.h"
#include "componentchoosergeo.h"
#include "componentchooserterminal.h"

ComponentChooserData::ComponentChooserData(QObject *parent, const QVariantList &args)
    : KCModuleData(parent, args)
    , m_browsers(new ComponentChooserBrowser(this))
    , m_fileManagers(new ComponentChooserFileManager(this))
    , m_terminalEmulators(new ComponentChooserTerminal(this))
    , m_emailClients(new ComponentChooserEmail(this))
    , m_geoUriHandlers(new ComponentChooserGeo(this))
{
    load();
}

void ComponentChooserData::load()
{
    m_browsers->load();
    m_fileManagers->load();
    m_terminalEmulators->load();
    m_emailClients->load();
    m_geoUriHandlers->load();
}

void ComponentChooserData::save()
{
    m_browsers->save();
    m_fileManagers->save();
    m_terminalEmulators->save();
    m_emailClients->save();
    m_geoUriHandlers->save();
}

void ComponentChooserData::defaults()
{
    m_browsers->defaults();
    m_fileManagers->defaults();
    m_terminalEmulators->defaults();
    m_emailClients->defaults();
    m_geoUriHandlers->defaults();
}

bool ComponentChooserData::isDefaults() const
{
    return m_browsers->isDefaults() && m_fileManagers->isDefaults() && m_terminalEmulators->isDefaults() && m_emailClients->isDefaults()
        && m_geoUriHandlers->isDefaults();
}

bool ComponentChooserData::isSaveNeeded() const
{
    return m_browsers->isSaveNeeded() || m_fileManagers->isSaveNeeded() || m_terminalEmulators->isSaveNeeded() || m_emailClients->isSaveNeeded()
        || m_geoUriHandlers->isSaveNeeded();
}

ComponentChooser *ComponentChooserData::browsers() const
{
    return m_browsers;
}

ComponentChooser *ComponentChooserData::fileManagers() const
{
    return m_fileManagers;
}

ComponentChooser *ComponentChooserData::terminalEmulators() const
{
    return m_terminalEmulators;
}

ComponentChooser *ComponentChooserData::emailClients() const
{
    return m_emailClients;
}

ComponentChooser *ComponentChooserData::geoUriHandlers() const
{
    return m_geoUriHandlers;
}
