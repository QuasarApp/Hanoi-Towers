/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "backEnd.h"
#include <cmath>
#include <QDataStream>
#include <QDir>
#include <qmlnotifyservice.h>
#include "gamestate.h"
#include <QQmlApplicationEngine>
#include <lvmainmodel.h>

constexpr unsigned char currentVersion = 6;

#define DEFAULT_USER "User"
#define FIRST_RUN_KEY "isFirstStart"
#define LVL_KEY "lvl"
#define ANIMATION_KEY "animation"
#define RANDOM_COLOR_KEY "randomColor"
#define CURRENT_PROFILE_KEY "currentProfile"

BackEnd::BackEnd(QQmlApplicationEngine *engine):
    QObject()
{
    _settings = QuasarAppUtils::Settings::get();

    connect(this, &BackEnd::profileChanged, [this](){
        _settings->setValue(CURRENT_PROFILE_KEY, profile());
    });

    init();
    setProfile(_settings->getStrValue(CURRENT_PROFILE_KEY, DEFAULT_USER));

    connect(&_client, &HanoiClient::statusChanged,
            this, &BackEnd::handleLogined);

    _loginModel = new LoginView::LVMainModel("userLogin");
    _loginModel->setComponents(LoginView::Nickname);
    _loginModel->init(engine);

    connect(_loginModel , &LoginView::LVMainModel::sigLoginRequest,
            this, &BackEnd::handleOnlineRequest);

    connect(_loginModel , &LoginView::LVMainModel::sigRegisterRequest,
            this, &BackEnd::handleOnlineRequest);

    connect(&_client , &HanoiClient::requestError,
            this, &BackEnd::handleOnlineRequestError);

}

void BackEnd::reset(){

    _settings->setValue(FIRST_RUN_KEY, true);
    _settings->setValue(LVL_KEY, 1);
    _settings->setValue(ANIMATION_KEY, true);
    _settings->setValue(RANDOM_COLOR_KEY, false);

    for (auto& item : _profileList) {
        item->deleteLater();
    }
    _profileList.clear();
    setProfile(addProfile(DEFAULT_USER, false)->name());

}

void BackEnd::init() {
    QFile f(MAIN_SETINGS_FILE);
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);

        unsigned char dataVersion;
        stream >> dataVersion;
        if (dataVersion == currentVersion) {
            // TO-DO - find solution of input data from pointers list

            int size;
            stream >> size;

            if (size * 10 > f.size()) {
                reset();
                return;
            }

            for (int i = 0; i < size; ++i ) {
                QString key;
                stream >> key;
                auto obj = addProfile(key, false);

                stream >> *obj;
                _profileList[key] = obj;

            }

            if (_profileList.isEmpty()) {
                setProfile(addProfile(DEFAULT_USER, false)->name());
            } else if (_profile.isEmpty()) {
                setProfile(_profileList.begin().key());

            }

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
            setShowHelp(isFirstStart);

            auto profile = addProfile(DEFAULT_USER, false);
            static_cast<GameState*>((profile->
                                    gameState()))->saveLvl(
                        static_cast<short>(lvl));

        }
        f.close();

    } else {
        reset();
    }

}

ProfileData* BackEnd::addProfile(const QString &userName, bool isOnlineuser) {
    auto profile = _profileList.value(userName, nullptr);
    if (profile) {
        return profile;
    }

    profile = new ProfileData(userName);

    connect(profile, &ProfileData::onlineRequest,
            this, &BackEnd::handleOnlineRequestfromProfile);


    profile->setOnline(isOnlineuser);

    _profileList[userName] = profile;

    emit profileListChanged();

    return profile;
}

void BackEnd::saveLocalData() const {
    QFile f(MAIN_SETINGS_FILE);

    QDir().mkpath(MAIN_FOLDER);

    if(f.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QDataStream stream(&f);
        stream << currentVersion;

        stream << static_cast<int>(_profileList.size());
        for (auto it = _profileList.begin(); it != _profileList.end(); ++it ) {
            stream << it.key();
            stream << *it.value();
        }

        f.close();
        return;
    }

    QuasarAppUtils::Params::log("local file data not opened on not created1 " + f.fileName(),
                                       QuasarAppUtils::Error);
}

void BackEnd::removeLocalUserData(const QString& name) {
    _profileList.remove(name);

    if (name == _profile && _profileList.size()) {
        setProfile(_profileList.begin().key());
    } else if (_profileList.isEmpty()) {
        reset();
    }

    emit profileListChanged();

}

void BackEnd::handleOnlineRequestfromProfile(const QString &name) {
    if (name != _profile) {
        return;
    }

    LoginView::UserData data;
    data.setNickname(name);
    _loginModel->setData(data);

    emit showOnlinePage();
}

void BackEnd::handleOnlineRequest(const LoginView::UserData & user) {

    if (!_client.login(user.nickname(), user.rawPassword().toLatin1())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Register online error"), tr("Failed to register this account, if this account was created by you, try to restore it."), "",
                    QmlNotificationService::NotificationData::Error);
    }

}

void BackEnd::handleOnlineRequestError(const QString &) {
    emit handleOnlineRequestfromProfile(_profile);
}

void BackEnd::handleLogined(int state) {

    if (state == 2) {
        auto logineduser = _client.user();
        _profileList[logineduser->mail()]->update(logineduser.data());
    }
}

bool BackEnd::randomColor() const {
    return _settings->getValue(RANDOM_COLOR_KEY, false).toBool();
}

void BackEnd::setRandomColor(bool random) {
    _settings->setValue(RANDOM_COLOR_KEY, random);
    emit randomColorChanged();
}

bool BackEnd::animation() const{
    return _settings->getValue(ANIMATION_KEY, true).toBool();
}

void BackEnd::setAnimation(bool name) {
    _settings->setValue(ANIMATION_KEY, name);
    emit animationChanged();
}

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return static_cast<unsigned short>(pow(2, lvl)) - 1;
}

bool BackEnd::isFirst()const{
    return _settings->getValue(FIRST_RUN_KEY, true).toBool();
}

void BackEnd::setShowHelp(bool state) {
    _settings->setValue(FIRST_RUN_KEY, state);
    emit firstChanged();

}

BackEnd::~BackEnd(){
    saveLocalData();
}

QString BackEnd::profile() const {
    return _profile;
}

QStringList BackEnd::profileList() {
    return _profileList.keys();
}

void BackEnd::createProfile(const QString &userName, bool isOnlineuser) {
    addProfile(userName, isOnlineuser);
}

//QObject *BackEnd::usersListModel() const {
//    return _usersList;
//}

QObject *BackEnd::profileObject() const {
    if (!_profileList.contains(_profile)) {
        return nullptr;
    }

    return _profileList[_profile];
}

QObject* BackEnd::gameState() {
    if (auto obj = dynamic_cast<ProfileData*>(profileObject())) {
        return obj->gameState();
    }

    return nullptr;
}

QObject *BackEnd::onlineStatus() {
    return &_client;
}

bool BackEnd::isOnline(const QString &name) {
    auto profile = _profileList.value(name, nullptr);
    if (!profile) {
        return false;
    }

    return profile->isOnline();
}

int BackEnd::record(const QString &name) {
    auto profile = _profileList.value(name, nullptr);
    if (!profile) {
        return 0;
    }

    return profile->record();
}

void BackEnd::removeUser(const QString &name) {
    auto profile = _profileList.value(name, nullptr);
    if (!profile) {
        return;
    }
    removeLocalUserData(name);

}

void BackEnd::setOnline(const QString &name, bool online) {
    auto profile = _profileList.value(name, nullptr);
    if (!profile) {
        return;
    }

    profile->setOnline(online);
}

void BackEnd::setProfile(QString profile) {
    if (!_profileList.contains(profile) || _profile == profile)
        return;

    _profile = profile;

    auto profileData = dynamic_cast<ProfileData*>(profileObject());

    if (profileData->isOnline()) {
        _client.setUser(profileData->userData());
        if (!_client.login()) {
            QmlNotificationService::NotificationService::getService()->setNotify(
                        tr("Login failed"),
                        tr("Failed to login %0, if this account was created by you, try to restore it.").arg(_profile),
                        "",
                        QmlNotificationService::NotificationData::Warning);
        }
    }

    emit profileChanged(_profile);
}

void BackEnd::setReward(int revard) {
    auto profile = _profileList.value(_profile, nullptr);
    if (!profile) {
        return;
    }

    if (profile->record() < revard) {
        profile->setRecord(revard);
    }
}

void BackEnd::removeOnlineProfile(QString) {
    // not supported

    if (!_client.removeProfile()) {

        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Remove online error"), tr("current profile not online!"), "",
                    QmlNotificationService::NotificationData::Warning);
    }

}
