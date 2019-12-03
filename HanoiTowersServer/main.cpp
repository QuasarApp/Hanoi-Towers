#include "hanoiserver.h"
#include <QCoreApplication>
#include <quasarapp.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QuasarAppUtils::Params::parseParams(argc, argv);

    HanoiServer server;
    return a.exec();
}
