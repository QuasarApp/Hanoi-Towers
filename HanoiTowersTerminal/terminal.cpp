#include "terminal.h"

Terminal::Terminal():Patronum::Controller("HanoiService") {

}

QString Terminal::defaultInstallLocation() {
    return QCoreApplication::applicationDirPath() + "/../ServerHanoiTowers.sh";
}

void Terminal::handleError(Patronum::ControllerError err) {
    Patronum::Controller::handleError(err);
    QCoreApplication::exit(static_cast<int>(err));
}
