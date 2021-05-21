/*
    SPDX-FileCopyrightText: 2020 Tobias Fella <fella@posteo.de>

    SPDX-License-Identifier: GPL-2.0-or-later

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the
    Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

#ifndef COMPONENTCHOOSERBROWSER_H
#define COMPONENTCHOOSERBROWSER_H

#include "componentchooser.h"

class ComponentChooserBrowser : public ComponentChooser
{
public:
    ComponentChooserBrowser(QObject *parent);

    void save() override;
};

#endif
