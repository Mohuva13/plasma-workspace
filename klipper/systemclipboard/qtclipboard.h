/*
    SPDX-FileCopyrightText: 2020 David Edmundson <davidedmundson@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#pragma once
#include "systemclipboard.h"

class QtClipboard : public SystemClipboard
{
public:
    explicit QtClipboard(QObject *parent);
    void setMimeData(QMimeData *mime, QClipboard::Mode mode) override;
    void clear(QClipboard::Mode mode) override;
    const QMimeData *mimeData(QClipboard::Mode mode) const override;
};
