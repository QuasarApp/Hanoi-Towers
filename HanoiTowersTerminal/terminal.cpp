#include "terminal.h"
#include <QCoreApplication>

Terminal::Terminal():Patronum::Controller("HanoiService",
                                          QCoreApplication::applicationDirPath() + "/../ServerHanoiTowers.sh") {

}

void Terminal::handleError(Patronum::ControllerError err) {
    Patronum::Controller::handleError(err);
    QCoreApplication::exit(static_cast<int>(err));
}
