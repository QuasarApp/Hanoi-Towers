#include "worldclient.h"

WorldClient::WorldClient(const QString &worldName): World(worldName) {

}

void WorldClient::bestUserChanged(const QString &bestUser) {
    emit sigBestUserChanged(bestUser);
}
