/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "worldupdate.h"

WorldUpdate::WorldUpdate(const QString &worldName) {
    _subscribeId = qHash(worldName);

}

bool WorldUpdate::isValid() const {
    return QH::PKG::AbstractData::isValid() && (_dataAddUpdate.size() || _dataRemove.size());
}

const QH::AccessToken &WorldUpdate::getSignToken() const {
    return _token;
}

unsigned int WorldUpdate::subscribeId() const {
    return _subscribeId;
}

QDataStream &WorldUpdate::fromStream(QDataStream &stream) {
    AbstractData::fromStream(stream);

    stream >> _dataAddUpdate;
    stream >> _dataRemove;
    stream >> _token;
    stream >> _subscribeId;
    stream >> _worldVersion;

    return stream;
}

QDataStream &WorldUpdate::toStream(QDataStream &stream) const {
    AbstractData::toStream(stream);

    stream << _dataAddUpdate;
    stream << _dataRemove;
    stream << _token;
    stream << _subscribeId;
    stream << _worldVersion;

    return stream;
}

unsigned int WorldUpdate::getWorldVersion() const {
    return _worldVersion;
}

void WorldUpdate::setWorldVersion(unsigned int worldVersion) {
    _worldVersion = worldVersion;
}

const QSet<UserPreview>& WorldUpdate::getDataRemove() const {
    return _dataRemove;
}

void WorldUpdate::setDataRemove(const QSet<UserPreview> &dataRemove) {
    _dataRemove = dataRemove;
}

const QSet<UserPreview>& WorldUpdate::getDataAddUpdate() const {
    return _dataAddUpdate;
}

void WorldUpdate::setDataAddUpdate(const QSet<UserPreview> &dataAddUpdate) {
    _dataAddUpdate = dataAddUpdate;
}
