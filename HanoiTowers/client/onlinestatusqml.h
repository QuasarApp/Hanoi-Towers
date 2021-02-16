/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#ifndef ONLINESTATUSQML_H
#define ONLINESTATUSQML_H
#include <QObject>
#include <singleserverclient.h>

using OnlineStatus = QH::ClientStatus;

class OnlineStatusQml
{
    Q_GADGET

    Q_PROPERTY(int offline READ offline)
    Q_PROPERTY(int connecting READ connecting)
    Q_PROPERTY(int connected READ connected)
    Q_PROPERTY(int loginning READ loginning)
    Q_PROPERTY(int loggined READ loggined)

public:
    OnlineStatusQml();

    Q_INVOKABLE int offline() const;
    Q_INVOKABLE int connecting() const;
    Q_INVOKABLE int connected() const;
    Q_INVOKABLE int loginning() const;
    Q_INVOKABLE int loggined() const;
};

Q_DECLARE_METATYPE(OnlineStatusQml)

#endif // ONLINESTATUSQML_H
