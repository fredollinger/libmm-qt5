/*
Copyright 2008,2011 Will Stephenson <wstephenson@kde.org>
Copyright 2010 Lamarque Souza <lamarque@kde.org>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MODEMMANAGER_MODEMGSMCONTACTSINTERFACE_H
#define MODEMMANAGER_MODEMGSMCONTACTSINTERFACE_H

#include "mmqt-export.h"

#include <QObject>
#include "modeminterface.h"

class ModemGsmContactsInterfacePrivate;

namespace ModemManager
{
class MMQT_EXPORT ModemGsmContactsInterface : public ModemInterface
{
Q_OBJECT
Q_DECLARE_PRIVATE(ModemGsmContactsInterface)

public:
    struct ContactType
    {
        int index;
        QString name,
        number;
    };

    typedef QList <ModemManager::ModemGsmContactsInterface::ContactType> ContactTypeList;

    ModemGsmContactsInterface(const QString & path, QObject * parent);
    ~ModemGsmContactsInterface();

    int addContact(const QString & name, const QString & number);
    void deleteContact(const int index);
    ContactType get(const int index);
    ModemManager::ModemGsmContactsInterface::ContactTypeList list();
    ModemManager::ModemGsmContactsInterface::ContactTypeList find(const QString & pattern);
    int getCount();
};
} // namespace ModemManager

#endif
