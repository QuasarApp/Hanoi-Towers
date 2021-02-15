#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#include <quasarapp.h>
#include <singleserver.h>

class UserData;

class HanoiServer : public QH::SingleServer
{
    Q_OBJECT
public:
    HanoiServer();

protected:
    QH::ParserResult parsePackage(const QH::Package &pkg,
                                  const QH::AbstractNodeInfo *sender) override;
    QStringList SQLSources() const override;

    QVariantMap defaultDbParams() const override;

private:
    bool workWirthUserData(const UserData *obj,
                           const QH::AbstractNodeInfo *sender,
                           const QH::Header *oldHeader = nullptr);



    // AbstractNode interface
protected:
    void nodeConfirmend(QH::AbstractNodeInfo *node) override;
};

#endif // SNAKESERVER_H
