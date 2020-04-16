#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

HanoiService::HanoiService(int argc, char *argv[]):
    QtService<QCoreApplication>(argc, argv, "HanoiService") {

}

void HanoiService::start() {
    if (!_server) {
        _server = new HanoiServer();
    }
}

void HanoiService::stop() {
    if (_server) {
        delete _server;
    }
}

void HanoiService::pause() {

}

void HanoiService::resume() {

}

void HanoiService::createApplication(int &argc, char **argv) {
    QuasarAppUtils::Params::parseParams(argc, argv);
    QtService<QCoreApplication>::createApplication(argc, argv);
}

