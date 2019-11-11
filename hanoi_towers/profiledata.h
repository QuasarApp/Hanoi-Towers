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
    Q_PROPERTY(bool onlineUser READ isOnline WRITE setOnline NOTIFY onlineChanged)

private:
    NetworkProtocol::UserData _userData;
    GameState _state;

private slots:
    void handleServerResponce(const NetworkProtocol::UserData &data);

public:
    ProfileData();
    ~ProfileData() override;

    Q_INVOKABLE QObject* gameState();

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE int record() const;
    Q_INVOKABLE bool isOnline() const;

    // StreamBase interface
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

public slots:
    void setOnline(bool onlineUser);
signals:
    void gameStateChanged(QObject* gameState);
    void onlineChanged(bool onlineUser);
    void onlineRequest();
};

#endif // PROFILEDATA_H
