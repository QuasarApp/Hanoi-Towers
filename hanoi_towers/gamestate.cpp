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
    if (save.size() > towerIndex)
        save[towerIndex] = tower;
}

bool GameState::load() {
    maxValueOfLoadedSave = 0;
    for ( auto &tower:  save) {
        for (int i : tower) {
            if (i > maxValueOfLoadedSave) {
                maxValueOfLoadedSave = i;
            }
        }
    }

    return true;

}
