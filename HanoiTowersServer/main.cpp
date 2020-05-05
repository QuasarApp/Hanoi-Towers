#include "hanoiservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("HanoiTowers Server"); // <--
    QCoreApplication::setOrganizationName("QuasarApp"); // <--
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--

    HanoiService server(argc, argv);
    return server.exec();
}
