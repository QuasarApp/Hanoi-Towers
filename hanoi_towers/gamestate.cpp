#include "gamestate.h"

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
    if (saves.contains(str)) {
        save = str;
        return true;
    }

    return false;

}

QDataStream& operator<< (QDataStream& stream, const GameState& file) {
    stream << file.saves;

    return stream;
}

QDataStream& operator>> (QDataStream& stream, GameState& file) {
    stream >> file.saves;

    return stream;
}
