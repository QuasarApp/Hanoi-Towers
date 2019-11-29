#ifndef SNAKESERVER_H
#define SNAKESERVER_H

#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_HANOI_PORT 7770

#define DEFAULT_DB QDir::homePath() + "/HanoiTowersDB/" + DEFAULT_DB_NAME

#include <quasarapp.h>
#include <ratingusernode.h>

class SnakeServer: public NetworkProtocol::RatingUserNode
{
    Q_OBJECT
public:
    SnakeServer();

    QVariantMap defaultDbParams() const override;
};

#endif // SNAKESERVER_H
