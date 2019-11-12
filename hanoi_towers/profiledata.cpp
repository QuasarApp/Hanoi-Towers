#include "profiledata.h"

void ProfileData::setOnline(bool onlineProfile) {
    if (onlineProfile != isOnline()) {
        if (onlineProfile) {
            emit onlineRequest();
        } else {
            emit onlineChanged(onlineProfile);
        }
    }
}

void ProfileData::handleServerResponce(const NetworkProtocol::UserData& data) {
    if (_userData.token() != data.token()) {
        _userData = data;
        emit onlineChanged(isOnline());
    }
}

ProfileData::ProfileData(const QString &name):
    QObject(nullptr) {
    _userData.setName(name);
}

ProfileData::~ProfileData() = default;

QObject *ProfileData::gameState() {
    return &_state;
}

QString ProfileData::name() const {
    return _userData.name();
}

int ProfileData::record() const {
    return _userData.extraData()["points"].toInt();
}

bool ProfileData::isOnline() const {
    return _userData.token().isValid();
}

QDataStream &ProfileData::fromStream(QDataStream &stream) {
    return stream >> _userData >> _state;
}

QDataStream &ProfileData::toStream(QDataStream &stream) const {
    return stream << _userData << _state;
}