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
     * @brief removeLocalUser This method remove user localy only.
     * @param userId user id to remove
     * @return true if user remove successful
     */
    bool removeLocalUser(const QString & userId);

    /**
     * @brief getUserData if the user with @a userId exists in cache then this method emit signal userDataChanged with user data
     * else send request to server.
     * This function find a object in next order:
     *  1. Search a object in local cache. if object findet but a client not subscribed to it then send subscribe.
     *  2. Search a object in local storage (data base). if object findet but a client not subscribed to it then send subscribe.
     *  3. Send request if object not findet.
     * @param userId
     * @param frce If this option will be sets to true then this method forced send request to server of object.
     * @return true if reqest send succesfull.
     */
    bool getUserData(const QString &userId);

    QH::ISqlDBCache * db() const;


    /**
     * @brief getUsersCache return a pointer to the cache of users.
     * @return
     */
    const QHash<QString, QSharedPointer<LocalUser> >*
    getUsersCache() const;

protected:
    QPair<QString, unsigned short> serverAddress() const override;
    bool initDatabase() override;

signals:
    void userDataChanged(QSharedPointer<LocalUser>);
    void sigBestuserIdChanged(const QString &userId);

    void worldChanged(QSharedPointer<WorldUpdate>);
    void worldInited(QHash<QString, UserPreview>);

private slots:
    void handleNewBestUser(QString userId);
    void handleCurrentUserChanged();

private:

    QSharedPointer<LocalUser> getLocalUser(const QString &userId) const;
    bool restUserData(const QString &userId);

    bool sendUserData(QSharedPointer<UserData> data);

    bool isOnline(const QSharedPointer<LocalUser>& data);
    bool isOnlineAndLoginned(const QSharedPointer<LocalUser>& data);

    bool workWithUserData(const QSharedPointer<UserData> & userData);
    void updateLocalCache(const QSharedPointer<LocalUser> &localUser);

    QHash<QString, QSharedPointer<LocalUser>> _usersCache;
    QSharedPointer<WorldClient> _world;
    QString _bestUserId;



};

Q_DECLARE_METATYPE(QSharedPointer<LocalUser>)

#endif // HANOICLIENT_H
