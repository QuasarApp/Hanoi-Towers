#include "gamestate.h"

int GameState::getMaxValueOfLoadedSaves() {
    return maxValueOfLoadedSave;
}

int GameState::getStep() const {
    return step;
}

void GameState::setStep(int value) {
    step = value;
}

GameState::GameState(const QString &savename) {

    save = savename;

    QList<QList<int>> towers;
    for (int i = 0 ; i < 3 ; i++)
        towers.push_back({});

    saves[save] = towers;
}

QList<int> GameState::getTower(int i) {
    return saves[save].value(i);
}

void GameState::setTower(int towerIndex ,const QList<int> &tower) {
    if (saves[save].size() > towerIndex)
        saves[save][towerIndex] = tower;
}

bool GameState::load(const QString &str) {
    save = str;

    if (saves.contains(str)) {
        maxValueOfLoadedSave = 0;
        for ( auto &tower:  saves[str]) {
            for (int i : tower) {
                if (i > maxValueOfLoadedSave) {
                    maxValueOfLoadedSave = i;
                }
            }
        }

        return true;
    } else {
        saves[str] = {QList<int>{},QList<int>{},QList<int>{}};
    }

    return false;

}

QDataStream& operator<< (QDataStream& stream, const GameState& file) {
    stream << file.step;
    stream << file.saves;

    return stream;
}

QDataStream& operator>> (QDataStream& stream, GameState& file) {
    stream >> file.step;
    stream >> file.saves;

    return stream;
}
