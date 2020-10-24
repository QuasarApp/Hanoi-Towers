/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QStringList>
#include <QObject>
#include <QHash>
#include <QDataStream>
#include <streambase.h>
#include "hanoitowersprotockol_global.h"

class HANOITOWERSPROTOCOL_EXPORT GameState : public QObject, public QH::StreamBase
{
   Q_OBJECT
   Q_PROPERTY(short lvl READ lvl WRITE saveLvl)

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

    // StreamBase interface
protected:
    QDataStream &fromStream(QDataStream &stream);
    QDataStream &toStream(QDataStream &stream) const;

private:
    QList<QList<int>> save;
    int maxValueOfLoadedSave = 0;
    int step = 0;

    short _lvl;

};


#endif // GAMESTATE_H
