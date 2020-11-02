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
#include <recordlistmodel.h>
#include <execution>

#define DEFAULT_USER_ID QByteArray("DefaultUser")
#define DEFAULT_USER_NAME "User"

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
    setProfile(_settings->getStrValue(CURRENT_PROFILE_KEY, DEFAULT_USER_ID));

    connect(&_client, &HanoiClient::statusChanged,
            this, &BackEnd::handleLogined);

    _loginModel = new LoginView::LVMainModel("userLogin", this);
    _loginModel->setComponents(LoginView::Nickname);
    _loginModel->init(engine);

    _recordsTable = new RecordListModel(this);

    connect(_loginModel , &LoginView::LVMainModel::sigLoginRequest,
            this, &BackEnd::handleOnlineRequest);

    connect(_loginModel , &LoginView::LVMainModel::sigRegisterRequest,
            this, &BackEnd::handleOnlineRequest);

    connect(&_client , &HanoiClient::requestError,
            this, &BackEnd::handleOnlineRequestError);

}

ProfileData* BackEnd::initProfile(const QByteArray& userId, const QString &userName) {
    if (_profile) {
        _profile->deleteLater();
    }

    _profile = new ProfileData(userId);

    connect(_profile, &ProfileData::onlineRequest,
            this, &BackEnd::handleOnlineRequestfromProfile);

    if (!_client.login(userId)) {
        _profile->setName(userName);

        if (!(_client.registerOflineUser(userId) && _client.updateProfile(*_profile))) {
            _profile->deleteLater();
            return nullptr;
        }

        return _profile;
    }

    *_profile = *_client.currentProfile();

    emit profileListChanged();

    return _profile;
}

void BackEnd::reset(){

    _settings->setValue(FIRST_RUN_KEY, true);
    _settings->setValue(LVL_KEY, 1);
    _settings->setValue(ANIMATION_KEY, true);
    _settings->setValue(RANDOM_COLOR_KEY, false);

    if (!initProfile(DEFAULT_USER_ID, DEFAULT_USER_NAME)) {
        throw std::runtime_error("Init default profile is failed!!! on the " + std::string(__func__) + " functions");
    }
}

void BackEnd::init() {
    QFile f(MAIN_SETINGS_FILE);
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);

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

        auto profile = initProfile(DEFAULT_USER_ID, DEFAULT_USER_NAME);
        if (!profile) {
            f.close();
            throw std::runtime_error("Init default profile is failed!!! on the " + std::string(__func__) + " functions");
        }

        static_cast<GameState*>((profile->
                                gameState()))->saveLvl(
                    static_cast<short>(lvl));


        f.close();
        f.remove();

    } else {
        reset();
    }

}

void BackEnd::handleOnlineRequestfromProfile(const QString &name) {

    LoginView::UserData data;
    data.setNickname(name);
    _loginModel->setData(data);

    emit showOnlinePage();
}

void BackEnd::handleOnlineRequest(const LoginView::UserData & user) {

    if (!_client.login(user.nickname().toLatin1(), user.rawPassword().toLatin1())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Register online error"),
                    tr("Failed to register this account, if this account was created by you, try to restore it."), "",
                    QmlNotificationService::NotificationData::Error);
    }

}

void BackEnd::handleOnlineRequestError(const QString &) {
    emit handleOnlineRequestfromProfile("");
}

void BackEnd::handleLogined(unsigned char state) {

    if (static_cast<Status>(state) == Status::Logined) {
        *_profile = *_client.currentProfile();
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

BackEnd::~BackEnd() {
    _client.updateProfile(*_profile);
}

QString BackEnd::profile() const {
    if (_profile)
        return _profile->name();
    return "";
}

QObject* BackEnd::profileList() {
    return _recordsTable;
}

bool BackEnd::createProfile(const QString& userId, const QString &userName) {

    auto usrId = userId.toLatin1();
    if (usrId != userId)
        return false;

    return initProfile(usrId, userName);
}

QObject *BackEnd::profileObject() const {
    return _profile;
}

QObject* BackEnd::gameState() {
    if (auto obj = dynamic_cast<ProfileData*>(profileObject())) {
        return obj->gameState();
    }

    return nullptr;
}

QObject *BackEnd::client() {
    return &_client;
}

void BackEnd::removeUser(const QByteArray &userId) {

    if (!_client.removeUser(userId)) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Remove online error"), tr("current profile not online!"), "",
                    QmlNotificationService::NotificationData::Warning);
    }
}

void BackEnd::setProfile(QString userId) {

    if (_client.login(userId.toLatin1())) {
        emit profileChanged(userId);
    }
}

void BackEnd::setReward(int revard) {

    if (_profile->record() < revard) {
        _profile->setRecord(revard);
    }
}
