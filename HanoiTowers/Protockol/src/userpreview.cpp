/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "userpreview.h"
#include <QDataStream>

UserPreview::UserPreview() {

}

UserPreview::UserPreview(const QString &id) {
    this->id = id;
}

QDataStream &UserPreview::fromStream(QDataStream &stream) {
    stream >> id;
    stream >> userName;
    stream >> record;

    return stream;
}

QDataStream &UserPreview::toStream(QDataStream &stream) const {
    stream << id;
    stream << userName;
    stream << record;

    return stream;
}

bool operator==(const UserPreview& left, const UserPreview& right) {
    return left.id == right.id;
}

uint qHash(const UserPreview &input) {
    return qHash(input.id);
}
