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
#include <QImage>
#include <databasenode.h>
#include <profiledata.h>
#include <userpreview.h>

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


    QString currentUserId() const;
    QSharedPointer<LocalUser> currentProfile() const;
    bool updateProfile(const LocalUser &user);
    bool addProfile(const LocalUser &);

    bool login(const QString &userId, const QString& rawPassword = "");
    bool registerOnlineUser(const QString &userId, const QString& rawPassword);

    bool removeUser(const QString &userId);

    void connectToServer(const QH::HostAddress& host);

    QList<UserPreview> localUsersPreview();

    // AbstractNode interface
    Status getStatus() const;
    void setStatus(const Status &status);

    bool setNewAvatar(const QString &userId, const QByteArray& image);
\

protected:
    void nodeConfirmend(const QH::HostAddress &node) override;
    void nodeConnected(const QH::HostAddress &node) override;
    void nodeDisconnected(const QH::HostAddress &node) override;
    QByteArray hashgenerator(const QByteArray &data) override;
    QStringList SQLSources() const override;

signals:
    void requestError(const QString & err);
    void statusChanged(unsigned char state);
    void profileIsUpdated();
    void profileChanged(QSharedPointer<LocalUser>);

private slots:
    void handleError(unsigned char status, const QString& error);

private:

    bool p_login(const QString &userId, const QByteArray &hashPassword = {});
    bool p_signIn(const QString &userId, const QByteArray &hashPassword);

    bool userDatarequest(const QByteArray &userId);
    QSharedPointer<LocalUser> getLocalUser(const QString &userId) const;

    bool sendUserData(const QSharedPointer<LocalUser>& data);

    bool isOnline(const QSharedPointer<LocalUser>& data);

    Status _status;
    QString _currentUserId;
    QH::HostAddress _serverAddress;
    QList<LocalUser*> _usersList;

};

#endif // HANOICLIENT_H
