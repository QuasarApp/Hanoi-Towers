#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

HanoiService::HanoiService(int argc, char *argv[]):
    Patronum::Service<QCoreApplication>(argc, argv, "HanoiService") {

}

HanoiService::~HanoiService() {
    onStop();
}

void HanoiService::onStart() {
    if (!_server) {
        _server = new HanoiServer();
    }
}

void HanoiService::onStop() {
    if (_server) {
        delete _server;
        _server = nullptr;
    }

    Service::onStop();
}

void HanoiService::handleReceive(const QList<Patronum::Feature> &data) {

    QList<Patronum::Feature> notSupported;
    for (const auto& i: data) {
        if (i.cmd() == "ping") {
            sendResuylt("Pong");
        } else if (i.cmd() == "Players") {
            //_server->
        } else {
            notSupported += i;
        }
    }

    Patronum::Service<QCoreApplication>::handleReceive(notSupported);
}

QList<Patronum::Feature> HanoiService::supportedFeatures() {
    QList<Patronum::Feature> data;

    data << Patronum::Feature("ping");
    data << Patronum::Feature("Players");

    return data;
}
