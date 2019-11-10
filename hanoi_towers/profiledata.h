#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"

#include <userdata.h>

class ProfileData : public QObject, public NetworkProtocol::StreamBase
{
    Q_OBJECT

    Q_PROPERTY(QObject* gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(int record READ record)

private:
    NetworkProtocol::UserData _userData;
    GameState _state;
    bool _onlineProfile;

public:
    ProfileData(bool isOnline = false);
    ~ProfileData() override;

    Q_INVOKABLE QObject* gameState();

    QString name() const;
    int record() const;

    // StreamBase interface
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    bool onlineProfile() const;
    void setOnlineProfile(bool onlineProfile);

signals:
    void gameStateChanged(QObject* gameState);

};

#endif // PROFILEDATA_H
