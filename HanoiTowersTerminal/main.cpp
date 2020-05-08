#include "terminal.h"

int main(int argc, const char *argv[])
{
    QCoreApplication::setApplicationName("HanoiTowers Terminal"); // <--
    QCoreApplication::setOrganizationName("QuasarApp"); // <--
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--


    Terminal terminal;
    if (!terminal.send(argc, argv)) {
        QuasarAppUtils::Params::log("command not sendet!", QuasarAppUtils::Error);
    }
    return terminal.waitForResponce();
}
