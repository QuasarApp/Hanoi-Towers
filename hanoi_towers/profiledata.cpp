#include "profiledata.h"

bool ProfileData::onlineProfile() const {
    return _onlineProfile;
}

void ProfileData::setOnlineProfile(bool onlineProfile) {
    _onlineProfile = onlineProfile;
}

ProfileData::ProfileData(bool isOnline) {
    _onlineProfile = isOnline;
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

QDataStream &ProfileData::fromStream(QDataStream &stream) {
    return stream >> _userData >> _state;
}

QDataStream &ProfileData::toStream(QDataStream &stream) const {
    return stream << _userData << _state;
}
