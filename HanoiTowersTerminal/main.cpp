#include "terminal.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("HanoiTowers Terminal"); // <--
    QCoreApplication::setOrganizationName("QuasarApp"); // <--
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--


    Terminal terminal;
    terminal.send(argc, argv);
    return terminal.waitForResponce();
}
