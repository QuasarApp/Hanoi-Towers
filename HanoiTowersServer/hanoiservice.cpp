#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

HanoiService::HanoiService(int argc, char *argv[]):
    Patronum::Service<QCoreApplication>(argc, argv, "HanoiService") {

}

HanoiService::~HanoiService() {
    stop();
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

void HanoiService::handleReceive(const QList<Patronum::Feature> &data) {
     Patronum::Service<QCoreApplication>::handleReceive(data);
}

QList<Patronum::Feature> HanoiService::supportedFeatures() {
    QList<Patronum::Feature> data;

    data << Patronum::Feature("ping");

    return data;
}
