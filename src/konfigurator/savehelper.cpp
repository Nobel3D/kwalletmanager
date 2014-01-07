/*
   Copyright (C) 2013 Valentin Rusu <kde@rusu.info>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "savehelper.h"

#include <kdebug.h>
#include <unistd.h>

#if defined(Q_WS_WIN)
// TODO: or rather use uid_t in the getuid() call below? or test for if __uid_t is present
#define __uid_t uid_t
#endif

ActionReply SaveHelper::save(QVariantMap args)
{
    __uid_t uid = getuid();
    kDebug() << "executing uid=" << uid;

    return ActionReply::SuccessReply;
}

KDE4_AUTH_HELPER_MAIN("org.kde.kcontrol.kcmkwallet", SaveHelper)
