#include "snakeserver.h"
#include <QCoreApplication>
#include <quasarapp.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QuasarAppUtils::Params::parseParams(argc, argv);

    SnakeServer server;
    return a.exec();
}
