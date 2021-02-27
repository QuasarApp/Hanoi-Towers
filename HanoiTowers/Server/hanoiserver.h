#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#include <quasarapp.h>
#include <singleserver.h>

class UserData;
class World;
class WorldUpdate;
class UserPreview;

class HanoiServer : public QH::SingleServer
{
    Q_OBJECT
public:
    HanoiServer();
    ~HanoiServer();

protected:
    QH::ParserResult parsePackage(const QSharedPointer<QH::PKG::AbstractData> &pkg,
                                  const QH::Header &pkgHeader,
                                  const QH::AbstractNodeInfo *sender) override;
    QStringList SQLSources() const override;

    QVariantMap defaultDbParams() const override;
    void nodeConfirmend(QH::AbstractNodeInfo *node) override;

    QH::ErrorCodes::Code deleteUser(const QSharedPointer<QH::PKG::UserMember> &user,
                                    const QH::AbstractNodeInfo *info) override;
    void memberSubsribed(const QVariant &clientId, unsigned int subscribeId) override;

private:
    bool workWirthUserData(const UserData *obj,
                           const QH::AbstractNodeInfo *sender,
                           const QH::Header *oldHeader = nullptr);

    void updateUserInWorld(const UserData* data);
    void removeUserFromWorld(const QString& userId);

    void updateWorld(const UserPreview& user, bool isRemove);
    QSharedPointer<WorldUpdate> getHistoryPoint(unsigned int version);

    World *_world = nullptr;
    QHash<unsigned int, QSharedPointer<WorldUpdate>> _worldHistory;
    mutable QMutex _worldHistoryMutexl;

};

#endif // SNAKESERVER_H
