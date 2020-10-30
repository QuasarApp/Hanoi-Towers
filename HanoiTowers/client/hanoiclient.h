/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef HANOICLIENT_H
#define HANOICLIENT_H

#ifdef RELEASE_BUILD
#define REMOTE_HOST "quasarapp.ddns.net"
#else
#define REMOTE_HOST "127.0.0.1"
#endif
#define REMOTE_PORT 7770
#include <databasenode.h>
#include <profiledata.h>

class LocalUser;
class UserData;

namespace QH {
namespace PKG {
class UserMember;
}
}

enum class Status: unsigned char {
    OfflineUser,
    Dissconnected,
    Connected,
    Logined
};

class HanoiClient: public QH::DataBaseNode
{
    Q_OBJECT
public:
    HanoiClient();

    QH::ParserResult parsePackage(const QH::Package &pkg,
                                  const QH::AbstractNodeInfo *sender) override;

    QStringList SQLSources() const override;

    QString currentUserName() const;

    ProfileData currentProfile();
    bool updateProfile(const ProfileData& profile);

    bool login(const QString& login, const QString& rawPassword = "");
    bool registerUser(const QString& login, const QString& rawPassword);
    bool removeUser(const QString& login);

    void connectToServer(const QH::HostAddress& host);

    // AbstractNode interface
    Status getStatus() const;
    void setStatus(const Status &status);

protected:
    void nodeConfirmend(const QH::HostAddress &node) override;
    void nodeConnected(const QH::HostAddress &node) override;
    void nodeDisconnected(const QH::HostAddress &node) override;
    QByteArray hashgenerator(const QByteArray &data) override;

signals:
    void requestError(const QString & err);
    void statusChanged(unsigned char state);
    void profileIsUpdated();

private slots:
    void handleError(unsigned char status, const QString& error);

private:

    bool p_login(const QString &userId, const QByteArray &hashPassword = {});
    bool p_signIn(const QString &userId, const QByteArray &hashPassword);

    bool userDatarequest(const QString &userId);
    const LocalUser *getLocalUser(const QString &userId) const;
    QSharedPointer<LocalUser> &&getEditableLocalUser(const QString &userId);


    ProfileData defaultProfile() const;

    Status _status;
    QString _currentUserName;
    QH::HostAddress _serverAddress;
    QList<LocalUser*> _usersList;

};

#endif // HANOICLIENT_H
