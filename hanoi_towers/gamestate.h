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
    int maxValueOfLoadedSave = 0;
    int step = 0;

public:
    explicit GameState(const QString& savename = "player");
    Q_INVOKABLE QList<int> getTower(int i);
    void setTower(int towerIndex, const QList<int> &tower);
    Q_INVOKABLE bool load(const QString& str);
    Q_INVOKABLE int getMaxValueOfLoadedSaves();

    friend QDataStream& operator<< (QDataStream& stream, const GameState& file);
    friend QDataStream& operator>> (QDataStream& stream, GameState& file);

    Q_INVOKABLE int getStep() const;
    void setStep(int value);
};

Q_DECLARE_METATYPE(GameState)


#endif // GAMESTATE_H
//#ifndef DIFF_H
//#define DIFF_H

//#include <QObject>

//class  Diff
//{
//    Q_GADGET
//private:
//    QList<int> removeIds;
//    QList<int> addedIds;
//public:
//    explicit Diff();

//    Q_INVOKABLE QList<int> getRemoveIds() const;
//    void setRemoveIds(const QList<int> &value);
//    Q_INVOKABLE QList<int> getAddedIds() const;
//    void setAddedIds(const QList<int> &value);
//};

//Q_DECLARE_METATYPE(Diff)

//#endif // DIFF_H
