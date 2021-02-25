#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#include <quasarapp.h>
#include <singleserver.h>

class UserData;
class World;

class HanoiServer : public QH::SingleServer
{
    Q_OBJECT
public:
    HanoiServer();

protected:
    QH::ParserResult parsePackage(const QSharedPointer<QH::PKG::AbstractData> &pkg,
                                  const QH::Header &pkgHeader,
                                  const QH::AbstractNodeInfo *sender) override;
    QStringList SQLSources() const override;

    QVariantMap defaultDbParams() const override;
    void nodeConfirmend(QH::AbstractNodeInfo *node) override;

private:
    bool workWirthUserData(const UserData *obj,
                           const QH::AbstractNodeInfo *sender,
                           const QH::Header *oldHeader = nullptr);


    World *_world = nullptr;

    // AbstractNode interface

};

#endif // SNAKESERVER_H
