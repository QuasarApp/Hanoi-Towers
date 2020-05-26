/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"
#include "userdata.h"

class ProfileData : public QObject, public NP::StreamBase
{
    Q_OBJECT

    Q_PROPERTY(QObject* gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(int record READ record WRITE setRecord NOTIFY recordChanged)
    Q_PROPERTY(bool onlineUser READ isOnline WRITE setOnline NOTIFY onlineChanged)

private:
    NP::UserData _userData;
    GameState _state;

private slots:
    void handleServerResponce(const NP::UserData &data);

public:
    ProfileData(const QString& name);
    ~ProfileData() override;

    Q_INVOKABLE QObject* gameState();

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE int record() const;
    Q_INVOKABLE bool isOnline() const;

    void update(const NP::UserData *newData);

    // StreamBase interface
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    const NP::UserData *userData() const;

public slots:
    void setOnline(bool onlineUser);
    void setRecord(int record);

signals:
    void gameStateChanged(QObject* gameState);
    void onlineChanged(bool onlineUser);
    void onlineRequest(const QString& name);
    void recordChanged(int record);
};

#endif // PROFILEDATA_H
