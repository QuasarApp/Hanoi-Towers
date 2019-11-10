#include "profiledata.h"

ProfileData::ProfileData() {

}

QObject *ProfileData::gameState() {
    return &_state;
}

void ProfileData::save() {
    _extraData["state"] = _state.toBytes();
}
