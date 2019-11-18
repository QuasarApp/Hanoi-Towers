#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QStringList>
#include <QObject>
#include <QHash>
#include <QDataStream>
#include <streambase.h>

class GameState : public QObject, public NetworkProtocol::StreamBase
{
   Q_OBJECT
   Q_PROPERTY(short lvl READ lvl WRITE saveLvl)

private:
    QList<QList<int>> save;
    int maxValueOfLoadedSave = 0;
    int step = 0;

    short _lvl;

    // StreamBase interface
protected:
    QDataStream &fromStream(QDataStream &stream);
    QDataStream &toStream(QDataStream &stream) const;

public:
    explicit GameState();
    Q_INVOKABLE QList<int> getTower(int i);
    Q_INVOKABLE void setTower(int towerIndex, const QList<int> &tower);
    Q_INVOKABLE bool load();
    Q_INVOKABLE int getMaxValueOfLoadedSaves();
    Q_INVOKABLE int lvl() const;

    Q_INVOKABLE int getStep() const;
    Q_INVOKABLE void setStep(int value);

    Q_INVOKABLE void unlockNextLvl();

public slots:
    void saveLvl(short lvl);
};


#endif // GAMESTATE_H
