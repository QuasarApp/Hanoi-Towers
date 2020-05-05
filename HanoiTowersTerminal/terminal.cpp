#include "terminal.h"

Terminal::Terminal():Patronum::Controller("HanoiService") {

}

QString Terminal::defaultInstallLocation() {
    return QCoreApplication::applicationDirPath() + "/../ServerHanoiTowers.sh";
}
