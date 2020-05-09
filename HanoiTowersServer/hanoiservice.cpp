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
        _server = nullptr;
    }
}

void HanoiService::pause() {

}

void HanoiService::resume() {

}

void HanoiService::handleReceive(const QList<Patronum::Feature> &data) {

    QList<Patronum::Feature> notSupported;
    for (const auto& i: data) {
        if (i.cmd() == "ping") {
            sendResuylt("Pong");
        } else {
            notSupported += i;
        }
    }

    Patronum::Service<QCoreApplication>::handleReceive(notSupported);
}

QList<Patronum::Feature> HanoiService::supportedFeatures() {
    QList<Patronum::Feature> data;

    data << Patronum::Feature("ping");

    return data;
}
