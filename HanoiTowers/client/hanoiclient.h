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
#include <singleclient.h>
#include <userpreview.h>

class LocalUser;
class UserData;
class World;
class WorldUpdate;
class WorldClient;

namespace QH {
namespace PKG {
class UserMember;
}
}

class HanoiClient: public QH::SingleClient
{
    Q_OBJECT
public:
    HanoiClient();
    ~HanoiClient();

    QH::ParserResult parsePackage(const QSharedPointer<QH::PKG::AbstractData> &pkg,
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
    bool subscribeToWorld();

    /**
     * @brief getUserData if the user with @a userId exits in cache then this method emit signal userDataChanged with user data
     * else send request to server.
     * @param userId
     * @return
     */
    bool getUserData(const QString &userId);

protected:
    QStringList SQLSources() const override;
    QH::HostAddress serverAddress() const override;
    void incomingData(QH::PKG::AbstractData *pkg, const QH::AbstractNodeInfo *sender) override;

signals:
    void userDataChanged(QSharedPointer<LocalUser>);
    void worldChanged(QSharedPointer<WorldUpdate>);
    void worldInited(QSet<UserPreview>);

private slots:
    void handleNewBestUser(QString userId);

private:

    QSharedPointer<LocalUser> getLocalUser(const QString &userId) const;

    bool sendUserData(QSharedPointer<UserData> data);

    bool isOnline(const QSharedPointer<LocalUser>& data);
    bool isOnlineAndLoginned(const QSharedPointer<LocalUser>& data);

    bool workWithUserData(const QSharedPointer<UserData> & userData);

    QHash<QString, QSharedPointer<LocalUser>> _usersCache;
    QSharedPointer<WorldClient> _world;
    QString _bestUserId;

};

Q_DECLARE_METATYPE(QSharedPointer<LocalUser>)

#endif // HANOICLIENT_H
