#include "backEnd.h"
#include <cmath>
#include <QDataStream>

BackEnd::BackEnd():
    QObject()
{
    isFirstStart = true;
    lvl = 1;

    readCnfig();
}

void BackEnd::writeConfig() const{
    QFile f(SAVE);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&f);
        stream << lvl;
        stream << isFirstStart;
        f.close();
    }
}

void BackEnd::readCnfig() {
    QFile f(SAVE);
    if(f.exists() && f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        stream >> lvl;
        stream >> isFirstStart;
        f.close();

        if(lvl < 1 || lvl > 99) {
            lvl = 1;
        }

        emit isFirstChanged();
    }
}

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return pow(2, lvl) - 1;
}

void BackEnd::save(const short &lvl){
    this->lvl = lvl;
    writeConfig();
}

bool BackEnd::isFirst()const{
    return isFirstStart;
}

void BackEnd::setShowHelp(bool state){
    isFirstStart = state;
    emit isFirstChanged();
    writeConfig();
}

short BackEnd::read()const{
    return lvl;
}

BackEnd::~BackEnd(){
    writeConfig();
}
