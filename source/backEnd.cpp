#include "backEnd.h"
#include <cmath>

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
        f.write((char*)(&isFirstStart), sizeof(isFirstStart));
        f.write((char*)(&lvl), sizeof(lvl));
        f.close();
    }
}

void BackEnd::readCnfig() {
    QFile f(SAVE);
    if(f.open(QIODevice::ReadOnly)){
        f.read((char*)&isFirstStart,sizeof(isFirstStart));
        f.read((char*)&lvl,sizeof(lvl));
        f.close();
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
