#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QStringList>
#include <QObject>
#include <QHash>
#include <QDataStream>

class GameState
{
   Q_GADGET
private:
    QHash<QString, QList<QList<int>>> saves;
    QString save;

public:
    GameState(const QString& savename = "player");
    Q_INVOKABLE QList<int> getTower(int i);
    Q_INVOKABLE void setTower(int towerIndex, const QList<int> &tower);
    Q_INVOKABLE bool load(const QString& str);

    friend QDataStream& operator<< (QDataStream& stream, const GameState& file);
    friend QDataStream& operator>> (QDataStream& stream, GameState& file);

};

#endif // GAMESTATE_H
