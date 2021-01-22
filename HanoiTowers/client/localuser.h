/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef LOCALUSER_H
#define LOCALUSER_H

#include "dbobject.h"
#include <accesstoken.h>
#include <profiledata.h>


class LocalUser: public QObject, public QH::PKG::DBObject
{
    Q_OBJECT

    Q_PROPERTY(GameState* gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString userId READ userId  NOTIFY userIdChanged)
    Q_PROPERTY(int record READ record WRITE setRecord NOTIFY recordChanged)
    Q_PROPERTY(int avatarHash READ avatarHash NOTIFY avatarChanged)
    Q_PROPERTY(bool onlineUser READ isOnline WRITE setOnline NOTIFY onlineChanged)

public:
    LocalUser();
    LocalUser(const QH::PKG::DBObject*);

    bool copyFrom(const QH::PKG::AbstractData *other) override;
    bool fromSqlRecord(const QSqlRecord &q) override;
    bool isValid() const override;

    // QOBJECT

    Q_INVOKABLE GameState* gameState();
    Q_INVOKABLE const GameState *gameState() const;

    Q_INVOKABLE QString userId() const;

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE int record() const;
    Q_INVOKABLE bool isOnline() const;
    Q_INVOKABLE int avatarHash() const;

    Q_INVOKABLE void setName(const QString& name);

    // QOBJECT END


    // DBObject interface
    bool online() const;

    QByteArray hashPassword() const;
    void setHashPassword(const QByteArray &hashPassword);

    QH::AccessToken token() const;
    void setToken(const QH::AccessToken &token);

    const ProfileData *userData() const;
    ProfileData *userData();
    void setUserData(const ProfileData &userData);

    int updateTime() const;
    void setUpdateTime(int updateTime);

    void setUserId(const QString& id);
    void setGameState(const GameState& state);
    void setGameState(const QByteArray& state);

    QByteArray avatarData() const;

public slots:
    void setOnline(bool online);
    void setRecord(int record);
    void setAvatar(const QByteArray& avatarHash);

signals:
    void userIdChanged(QString);
    void gameStateChanged(const GameState*);
    void nameChanged(QString);
    void recordChanged(int);
    void avatarChanged(int);

    void onlineChanged(bool onlineUser);

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QH::PKG::DBObject *createDBObject() const override;
    QString primaryKey() const override;

private:
    QByteArray _hashPassword;
    QH::AccessToken _token;
    ProfileData _userData;
    int _updateTime = 0;
    unsigned int _avatarHash = 0;



};

#endif // LOCALUSER_H
