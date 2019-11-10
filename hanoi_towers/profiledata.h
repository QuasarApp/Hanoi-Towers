#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"

#include <userdata.h>

class ProfileData : public QObject, public NetworkProtocol::UserData
{
    Q_OBJECT
    Q_PROPERTY(QObject* gameState READ gameState NOTIFY gameStateChanged)
private:
    GameState _state;

public:
    ProfileData();
    Q_INVOKABLE QObject* gameState();

    void save();


signals:
    void gameStateChanged(QObject* gameState);
};

#endif // PROFILEDATA_H
