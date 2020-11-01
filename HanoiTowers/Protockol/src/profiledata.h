/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"
#include "hanoitowersprotockol_global.h"

class HANOITOWERSPROTOCOL_EXPORT ProfileData : public QObject, public QH::StreamBase
{
    Q_OBJECT

    Q_PROPERTY(QObject* gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString userId READ userId NOTIFY userIdChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int record READ record WRITE setRecord NOTIFY recordChanged)
    Q_PROPERTY(bool onlineUser READ isOnline WRITE setOnline NOTIFY onlineChanged)


public:
    ProfileData(const QByteArray &userID);
    ProfileData(const ProfileData& oither);

    ~ProfileData() override;

    Q_INVOKABLE QObject* gameState();

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE int record() const;
    Q_INVOKABLE bool isOnline() const;

    void setName(const QString& name);

    // StreamBase interface
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    ProfileData& operator = (const ProfileData& right);

    QString userId() const;
    QByteArray userIdRaw() const;

public slots:
    void setOnline(bool onlineUser);
    void setRecord(int record);

signals:
    void gameStateChanged(QObject* gameState);
    void onlineChanged(bool onlineUser);
    void onlineRequest(const QString& name);
    void recordChanged(int record);
    void nameChanged(QString name);

    void userIdChanged(QString userId);

private:
    GameState _state;
    QString _name;
    int _record = 0;
    bool _online = false;
    QByteArray _userId;
};



#endif // PROFILEDATA_H
