#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#define DEFAULT_ADDRESS ""
#define DEFAULT_HANOI_PORT 7770

#include <quasarapp.h>
#include <databasenode.h>

class HanoiServer : public QH::DataBaseNode
{
//    Q_OBJECT
public:
    HanoiServer();

protected:
    QH::ParserResult parsePackage(const QH::Package &pkg,
                                  const QH::AbstractNodeInfo *sender) override;
    QStringList SQLSources() const override;

    QVariantMap defaultDbParams() const override;

    // DataBaseNode interface
protected:
};

#endif // SNAKESERVER_H
