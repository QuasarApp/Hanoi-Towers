#include "backEnd.h"
#include <cmath>
#include <QDataStream>
#include <QDir>

BackEnd::BackEnd():
    QObject()
{
    _settings = QuasarAppUtils::Settings::get();
}

void BackEnd::reset(){

    _settings->setValue("isFirstStart", true);
    _settings->setValue("lvl", 1);
    _settings->setValue("animation", true);
    _settings->setValue("randomColor", false);

    if (_gameState) {
        _gameState->deleteLater();
    }

    _gameState = new GameState();

}

void BackEnd::writeConfig() const {
    _settings->sync();
}

bool BackEnd::randomColor() const {
    return _settings->getValue("randomColor", false).toBool();
}

void BackEnd::setRandomColor(bool random) {
    _settings->setValue("randomColor", random);
    emit randomColorChanged();
}

bool BackEnd::animation() const{
    return _settings->getValue("animation", true).toBool();
}

void BackEnd::setAnimation(bool name) {
    _settings->setValue("animation", name);
    emit animationChanged();
}

void BackEnd::readCnfig() {
    QFile f(MAIN_SETINGS_FILE);
    if(f.exists() && f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        unsigned short lvl;
        bool isFirstStart, _animation, _randomColor;
        stream >> lvl;
        stream >> isFirstStart;
        stream >> _animation;
        stream >> _randomColor;

        stream >> _gameState;

        f.close();

        if(lvl < 1 || lvl > 99) {
            lvl = 1;
        }

        setAnimation(_animation);
        setRandomColor(_randomColor);
        setRandomColor(isFirstStart);

        emit firstChanged();
    }
}

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return static_cast<unsigned short>(pow(2, lvl)) - 1;
}

void BackEnd::save(short lvl){
    _settings->setValue("lvl", static_cast<unsigned short>(lvl));
}

bool BackEnd::isFirst()const{
    return _settings->getValue("isFirstStart", true).toBool();
}

void BackEnd::setShowHelp(bool state) {
    _settings->setValue("isFirstStart", state);
    emit firstChanged();

}

short BackEnd::read()const{
    return static_cast<short>(_settings->getValue("lvl", 1).toInt());
}

BackEnd::~BackEnd(){
    writeConfig();

    if (_gameState) {
        delete _gameState;
    }
}

QString BackEnd::profile() const {
    return _localProfilesList.value(_profileIndex);
}

QStringList BackEnd::profileList() const {
    return _localProfilesList;
}

int BackEnd::profileIndex() const {
    return _profileIndex;
}

QObject* BackEnd::gameState() {
    return _gameState;
}

void BackEnd::setProfileList(QStringList profileList) {
    if (_localProfilesList == profileList)
        return;

    _localProfilesList = profileList;
    emit profileListChanged(_localProfilesList);
}
