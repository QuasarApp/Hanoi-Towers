/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "gamestate.h"

int GameState::getMaxValueOfLoadedSaves() {
    return maxValueOfLoadedSave;
}

int GameState::lvl() const {
    return _lvl;
}

int GameState::getStep() const {
    return step;
}

void GameState::setStep(int value) {
    step = value;
}

void GameState::unlockNextLvl() {
    maxValueOfLoadedSave++;
    _lvl = static_cast<short>(maxValueOfLoadedSave);
}

bool GameState::fSavedGame() const {
    for (const auto &tower: qAsConst(save) ) {
        if (tower.size()) {
            return true;
        }
    }

    return false;
}

void GameState::saveLvl(short lvl) {
    _lvl = lvl;
}

QDataStream &GameState::fromStream(QDataStream &stream) {
    stream >> step;
    stream >> save;
    stream >> _lvl;

    return stream;
}

QDataStream &GameState::toStream(QDataStream &stream) const {
    stream << step;
    stream << save;
    stream << _lvl;

    return stream;
}

GameState::GameState() {

    save.clear();
    for (int i = 0 ; i < 3 ; i++)
        save.push_back({});
}

QList<int> GameState::getTower(int i) {
    return save.value(i);
}

void GameState::setTower(int towerIndex ,const QList<int> &tower) {
    if (save.size() > towerIndex) {
        save[towerIndex] = tower;
        emit fSavedGameChanged();
    }
}

bool GameState::load() {
    maxValueOfLoadedSave = 1;
    for ( auto &tower:  save) {
        for (int i : tower) {
            if (i > maxValueOfLoadedSave) {
                maxValueOfLoadedSave = i;
            }
        }
    }

    return true;

}

bool operator == (const GameState& left, const GameState& right) {
    return left._lvl == right._lvl &&
            left.save == right.save &&
            left.step == right.step &&
            left.maxValueOfLoadedSave == right.maxValueOfLoadedSave;
}
