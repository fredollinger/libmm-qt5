/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -p mm-modem-cdmainterface /home/ilia/libnm-qt/solid/modemmanager-0.4/dbus/introspection/mm-modem-cdma.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MM_MODEM_CDMAINTERFACE_H
#define MM_MODEM_CDMAINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "generic-types.h"

/*
 * Proxy class for interface org.freedesktop.ModemManager.Modem.Cdma
 */
class OrgFreedesktopModemManagerModemCdmaInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.ModemManager.Modem.Cdma"; }

public:
    OrgFreedesktopModemManagerModemCdmaInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopModemManagerModemCdmaInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString> GetEsn()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetEsn"), argumentList);
    }

    inline QDBusPendingReply<uint, uint> GetRegistrationState()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetRegistrationState"), argumentList);
    }
    inline QDBusReply<uint> GetRegistrationState(uint &evdo_state)
    {
        QList<QVariant> argumentList;
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("GetRegistrationState"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            evdo_state = qdbus_cast<uint>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<ModemManager::ModemCdmaInterface::ServingSystemType> GetServingSystem()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetServingSystem"), argumentList);
    }

    inline QDBusPendingReply<uint> GetSignalQuality()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetSignalQuality"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void RegistrationStateChanged(uint cdma_1x_state, uint evdo_state);
    void SignalQuality(uint quality);
};

#endif
