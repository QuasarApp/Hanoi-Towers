#include "hanoiserver.h"
#include <QDir>
#include <QNetworkInterface>

HanoiServer::HanoiServer() {

    QString address = DEFAULT_ADDRESS;
    unsigned short port = DEFAULT_HANOI_PORT;

    if (QuasarAppUtils::Params::isEndable("address")) {
        auto addressList = QuasarAppUtils::Params::getStrArg("address").split(":");
        if (address.size() != 2) {

            QuasarAppUtils::Params::log("invalid address params",
                                               QuasarAppUtils::Error);
            abort();
        }

        address = addressList.first();
        port = static_cast<decltype (port)>(addressList.last().toInt());
    }

    if (!run(address, port)) {
        QuasarAppUtils::Params::log("fail to run server",
                                           QuasarAppUtils::Error);
        abort();
    }

}

QVariantMap HanoiServer::defaultDbParams() const {
    return {
        {"DBDriver", "QSQLITE"},
        {"DBFilePath", DEFAULT_DB_PATH},
        {"DBInitFile", DEFAULT_DB_INIT_FILE_PATH}
    };
}
