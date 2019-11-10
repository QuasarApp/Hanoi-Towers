#include "backEnd.h"
#include <cmath>
#include <QDataStream>
#include <QDir>
#include "gamestate.h"

constexpr unsigned char currentVersion = 6;

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

    for (auto& item : _profileList) {
        item->deleteLater();
    }
    _profileList.clear();
    emit profileListChanged();

}

bool BackEnd::init() {
    QFile f(MAIN_SETINGS_FILE);
    if(f.exists() && f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);

        unsigned char dataVersion;
        stream >> dataVersion;
        if (dataVersion != currentVersion) {
            stream >> _profileList;
            stream >> _profile;

            f.close();
        } else {
            unsigned short lvl;
            bool isFirstStart, _animation, _randomColor;
            stream >> lvl;
            stream >> isFirstStart;
            stream >> _animation;
            stream >> _randomColor;

            if(lvl < 1 || lvl > 99) {
                lvl = 1;
            }

            setAnimation(_animation);
            setRandomColor(_randomColor);
            setRandomColor(isFirstStart);

            auto profile = _profileList.value("User", nullptr);
            if (!profile) {
                profile = new ProfileData();
                _profileList["User"] = profile;
            }

            static_cast<GameState*>((profile->
                                    gameState()))->saveLvl(
                        static_cast<short>(lvl));

            emit firstChanged();
        }

        return true;
    }

    return false;
}

void BackEnd::saveLocalData() const {
    QFile f(MAIN_SETINGS_FILE);

    if(f.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QDataStream stream(&f);
        stream << currentVersion;
        stream << _profileList;
        stream << _profile;

        f.close();
        return;
    }

    QuasarAppUtils::Params::verboseLog("local file data not opened on not created1 " + f.fileName(),
                                       QuasarAppUtils::Error);
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

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return static_cast<unsigned short>(pow(2, lvl)) - 1;
}

bool BackEnd::isFirst()const{
    return _settings->getValue("isFirstStart", true).toBool();
}

void BackEnd::setShowHelp(bool state) {
    _settings->setValue("isFirstStart", state);
    emit firstChanged();

}

BackEnd::~BackEnd(){
    saveLocalData();
}

QString BackEnd::profile() const {
    return _profile;
}

QStringList BackEnd::profileList() const {
    return _profileList.keys();
}

QObject* BackEnd::gameState() {
    if (!_profileList.contains(_profile)) {
        return nullptr;
    }

    return _profileList[_profile]->gameState();
}
