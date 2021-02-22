/*
 * Copyright (C) 2018-2021 QuasarApp.
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
#include <singleserverclient.h>
#include <userpreview.h>

class LocalUser;
class UserData;

namespace QH {
namespace PKG {
class UserMember;
}
}

class HanoiClient: public QH::SingleServerClient
{
    Q_OBJECT
public:
    HanoiClient();

    QH::ParserResult parsePackage(QH::PKG::AbstractData *pkg,
                                  const QH::Header &pkgHeader,
                                  const QH::AbstractNodeInfo *sender) override;


    QString currentUserId() const;
    QSharedPointer<LocalUser> currentProfile() const;
    bool updateProfile(const LocalUser &user);
    bool addProfile(const LocalUser &);
    bool setProfile(const QString &userId,
                    QSharedPointer<LocalUser> *selectedProfileData = nullptr);

    QList<UserPreview> localUsersPreview();

    bool setNewAvatar(const QString &userId, const QByteArray& image);
\

protected:
    QStringList SQLSources() const override;
    QH::HostAddress serverAddress() const override;
    void incomingData(QH::PKG::AbstractData *pkg, const QH::AbstractNodeInfo *sender) override;

signals:
    void profileChanged(QSharedPointer<LocalUser>);
private:

    bool userDatarequest(const QByteArray &userId);
    QSharedPointer<LocalUser> getLocalUser(const QString &userId) const;

    bool sendUserData(QSharedPointer<UserData> data);

    bool isOnline(const QSharedPointer<LocalUser>& data);
    bool isOnlineAndLoginned(const QSharedPointer<LocalUser>& data);

    QList<LocalUser*> _usersList;

};

Q_DECLARE_METATYPE(QSharedPointer<LocalUser>)

#endif // HANOICLIENT_H
