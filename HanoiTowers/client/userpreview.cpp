/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "userpreview.h"


UserPreview::UserPreview() {

}

UserPreview::UserPreview(const QString &id) {
    this->id = id;
}

bool operator==(const UserPreview& left, const UserPreview& right) {
    return left.id == right.id;
}
