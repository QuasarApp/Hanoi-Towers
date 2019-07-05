#include "backEnd.h"
#include <cmath>
#include <QDataStream>
#include <QDir>

BackEnd::BackEnd():
    QObject()
{
    reset();
    readCnfig();
}

void BackEnd::reset(){
    isFirstStart = true;
    lvl = 1;
    _animation = true;
    _randomColor = false;
}

void BackEnd::writeConfig() const {
    QDir dir(QDir::rootPath());

    if (!QFileInfo::exists(MAIN_FOLDER) &&
        !dir.mkpath(MAIN_FOLDER)) {
        return;
    }

    QFile f(MAIN_SETINGS_FILE);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&f);
        stream << lvl;
        stream << isFirstStart;
        stream << _animation;
        stream << _randomColor;
        f.close();
    }
}

bool BackEnd::randomColor() const {
    return _randomColor;
}

void BackEnd::setRandomColor(bool random) {
    if (_randomColor != random) {
        _randomColor = random;
        writeConfig();
        emit randomColorChanged();
    }

}

bool BackEnd::animation() const{
    return _animation;
}

void BackEnd::setAnimation(bool name) {
    if (_animation != name) {
        _animation = name;
        writeConfig();
        emit animationChanged();
    }

}

void BackEnd::readCnfig() {
    QFile f(MAIN_SETINGS_FILE);
    if(f.exists() && f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        stream >> lvl;
        stream >> isFirstStart;
        stream >> _animation;
        stream >> _randomColor;

        if (f.size() <= 3) {
            reset();
        }
        f.close();

        if(lvl < 1 || lvl > 99) {
            lvl = 1;
        }

        emit firstChanged();
    } else {
        QFile f(SAVE);
        if(f.exists() && f.open(QIODevice::ReadOnly)){
            QDataStream stream(&f);
            stream >> lvl;
            stream >> isFirstStart;
            stream >> _animation;
            stream >> _randomColor;

            if (f.size() <= 3) {
                reset();
            }
            f.close();

            if(lvl < 1 || lvl > 99) {
                lvl = 1;
            }

            emit firstChanged();
        }
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
    emit firstChanged();
    writeConfig();
}

short BackEnd::read()const{
    return lvl;
}

BackEnd::~BackEnd(){
    writeConfig();
}
