/*
 * Copyright (C) 2018-2021 QuasarApp.
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
#include "hanoiimageprovider.h"
#include <QQmlApplicationEngine>
#include <lvmainmodel.h>
#include <recordlistmodel.h>
#include <QQmlContext>
#include <QBuffer>
#include <QCoreApplication>
#include "dataconverter.h"
#include "localuser.h"

#define DEFAULT_USER_ID "DefaultUser"
#define DEFAULT_USER_NAME "User"

#define FIRST_RUN_KEY "isFirstStart"
#define ANIMATION_KEY "animation"
#define RANDOM_COLOR_KEY "randomColor"
#define CURRENT_PROFILE_KEY "currentProfile"
#define FOG "fog"
#define FOG_ANIMATION "fogAnimation"

BackEnd::BackEnd(QQmlApplicationEngine *engine):
    QObject(),
    _profile()
{
    _settings = QuasarAppUtils::Settings::get();

    _client = new HanoiClient();
    _loginModel = new LoginView::LVMainModel("userLogin", this);
    _createNewOfflineUser = new LoginView::LVMainModel("createUser", this);

    _recordsTable = new RecordListModel(this);
    _imageProvider = new HanoiImageProvider(&_profile);
    _dataConverter = new DataConverter;

    _loginModel->setComponents(LoginView::Nickname |
                               LoginView::Title |
                               LoginView::Password |
                               LoginView::SigupPage |
                               LoginView::LoginPage |
                               LoginView::TermOfUse);

    _loginModel->setCurrentPage(LoginView::ViewComponents::LoginPage);
    _loginModel->init(engine);

    _createNewOfflineUser->setComponents(LoginView::Nickname |
                                         LoginView::SigupPage |
                                         LoginView::Title);
    _createNewOfflineUser->setAcceptButtonText(tr("Create new user"));
    _createNewOfflineUser->init(engine);

    _recordsTable->setSource(_client->localUsersPreview());

    engine->addImageProvider("HanoiImages", _imageProvider);


    connect(_loginModel , &LoginView::LVMainModel::sigLoginRequest,
            this, &BackEnd::handleOnlineRequest);

    connect(_loginModel , &LoginView::LVMainModel::sigRegisterRequest,
            this, &BackEnd::handleOnlineRegisterRequest);

    connect(_createNewOfflineUser , &LoginView::LVMainModel::sigRegisterRequest,
            this, &BackEnd::handleCreateNewProfile);

    connect(_client , &HanoiClient::requestError,
            this, &BackEnd::handleOnlineRequestError);

    connect(_client , &HanoiClient::profileChanged,
            this, &BackEnd::handleProfileChanged);

    connect(_client , &HanoiClient::statusChanged,
            this, &BackEnd::setOnlineStatus);

    connect(&_profile, &LocalUser::nameChanged,
            this, &BackEnd::handleChangeName);

    setProfile(_settings->getStrValue(CURRENT_PROFILE_KEY, DEFAULT_USER_ID));
    init();

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

        setAnimation(_animation);
        setRandomColor(_randomColor);
        setShowHelp(isFirstStart);


        f.close();
        f.remove();

    } else {
        _settingsData.animation = _settings->getValue(ANIMATION_KEY, true).toBool();
        _settingsData.randomColor = _settings->getValue(RANDOM_COLOR_KEY, false).toBool();
        _settingsData.fog = _settings->getValue(FOG, true).toBool();
        _settingsData.fogAnimation = _settings->getValue(FOG_ANIMATION, true).toBool();

    }

}

void BackEnd::onlineRequest(const QString &userId) {

    if (_profile.token().isValid() && _client->login(userId)) {
        return;
    }

    LoginView::UserData data;
    data.setNickname(userId);
    _loginModel->setData(data);

    if (!_client->isConnected() && !_client->connectToServer()) {

        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Connect error"),
                    tr("Failed to connect to server"
                       " please check network connection befor login"), "",
                    QmlNotificationService::NotificationData::Error);

        return;
    }

    emit showOnlinePage();
}

int BackEnd::onlineStatus() const {
    return static_cast<int>(_onlineStatus);
}

void BackEnd::handleChangeName(const QString & name) {
    emit profileChanged(name);
}

void BackEnd::handleCreateNewProfile(const LoginView::UserData & data) {
    createProfile(data.nickname(), data.nickname());
}

void BackEnd::handleOnlineRequest(const LoginView::UserData & user) {

    if (!_client->login(user.nickname(), user.rawPassword())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("login error"),
                    tr("Failed to login into online account,"
                       " please check your password and username"), "",
                    QmlNotificationService::NotificationData::Error);

    }
}

void BackEnd::handleOnlineRegisterRequest(const LoginView::UserData &user) {
    if (!_client->signup(user.nickname(), user.rawPassword())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Register online error"),
                    tr("Failed to register this account,"
                       " if this account was created by you, try to restore it."), "",
                    QmlNotificationService::NotificationData::Error);
    }
}

void BackEnd::handleOnlineRequestError(QH::ErrorCodes::Code code, const QString & err) {

    auto errMessage = [](const QString &err) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Server error"),
                    err, "",
                    QmlNotificationService::NotificationData::Error);
    };

    if (code == QH::ErrorCodes::UserNotExits) {
        _loginModel->setCurrentPage(LoginView::ViewComponents::SigupPage);
        errMessage(tr("User with this id is not registered. If it you then use please the sigup form."));
        emit showOnlinePage();

        return;
    }

    if (code == QH::ErrorCodes::UserExits) {
        _loginModel->setCurrentPage(LoginView::ViewComponents::LoginPage);
        errMessage(tr("User with this id already registered. If it you then use please the login form."));
        emit showOnlinePage();

        return;
    }

    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Server error"),
                err, "",
                QmlNotificationService::NotificationData::Error);
}

void BackEnd::handleProfileChanged(QSharedPointer<LocalUser> profileId) {
    _profile.copyFrom(profileId.data());
    _settings->setValue(CURRENT_PROFILE_KEY, _profile.getId());

    emit profileChanged(_profile.getId().toString());
}

bool BackEnd::randomColor() const {
    return _settings->getValue(RANDOM_COLOR_KEY, false).toBool();
}

void BackEnd::setRandomColor(bool random) {

    if (_settingsData.randomColor != random) {

        _settings->setValue(RANDOM_COLOR_KEY, random);
        _settingsData.randomColor = random;
        emit randomColorChanged();
    }
}

bool BackEnd::animation() const{
    return _settings->getValue(ANIMATION_KEY, true).toBool();
}

void BackEnd::setAnimation(bool value) {
    if (_settingsData.animation != value) {

        _settings->setValue(ANIMATION_KEY, value);
        _settingsData.animation = value;
        emit animationChanged();
    }
}

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return static_cast<unsigned short>(pow(2, lvl)) - 1;
}

bool BackEnd::isFirst()const{
    return _settings->getValue(FIRST_RUN_KEY, true).toBool();
}

void BackEnd::setShowHelp(bool state) {
    _settings->setValue(FIRST_RUN_KEY, state);
}

void BackEnd::setNewAvatar(QString pathToAvatar) {
    if (pathToAvatar.contains("file://")) {
        pathToAvatar = pathToAvatar.right(pathToAvatar.size() - 7);
    }

    QImage img(pathToAvatar);
    int maxSize = std::max(img.size().width(), img.size().height());
    bool widthIsLarge = maxSize == img.size().width();
    if (maxSize > 200) {
        if (widthIsLarge) {
            img = img.scaledToWidth(200,
                                    Qt::TransformationMode::SmoothTransformation);

        } else {
            img = img.scaledToHeight(200,
                                    Qt::TransformationMode::SmoothTransformation);
        }
    }

    QByteArray arr;
    QBuffer buf(&arr);
    buf.open(QIODevice::WriteOnly);
    img.save(&buf, "PNG");
    buf.close();

    _profile.setAvatar(arr);

}

bool BackEnd::fog() const {
    return _settings->getValue(FOG, true).toBool();
}

bool BackEnd::fogAnimation() const {
    return _settings->getValue(FOG_ANIMATION, true).toBool();
}

BackEnd::~BackEnd() {
    _client->updateProfile(_profile);
    QCoreApplication::processEvents();

    _imageProvider->stop();
    _client->softDelete();

    delete _dataConverter;
}

QString BackEnd::profile() const {
    return _profile.name();
}

QObject* BackEnd::profileList() {
    return _recordsTable;
}

bool BackEnd::createProfile(const QString& userId, const QString &userName) {

    LocalUser user;
    user.setName(userName);
    user.setUserId(userId);

    if (!_client->addProfile(user)) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Create user error"),
                    tr("Failed to create a new user, The name %0 alredy used.").arg(userId), "",
                    QmlNotificationService::NotificationData::Error);
        return false;

    }

    _recordsTable->updateSourceItem(_dataConverter->toUserPreview(user));

    return true;
}

QObject *BackEnd::profileObject() {
    return &_profile;
}

GameState *BackEnd::gameState() {
    if (auto obj = dynamic_cast<LocalUser*>(profileObject())) {
        return obj->gameState();
    }

    return nullptr;
}

QObject *BackEnd::client() {
    return _client;
}

void BackEnd::removeUser(const QString &userId) {

    if (!_client->removeUser()) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Remove online error"), tr("current profile not online!"), "",
                    QmlNotificationService::NotificationData::Warning);
    }

    _recordsTable->removeSourceItem(userId);

    auto userID = _recordsTable->data(QModelIndex(), RecordListModel::UserId).toString();

    if (userID.isEmpty()) {
        userID = DEFAULT_USER_ID;
    }

    setProfile(userID);

}

void BackEnd::setProfile(QString userId) {
    if (!_client)
        return;

    _client->updateProfile(_profile);

    if (_client->setProfile(userId)) {
        emit profileChanged(userId);

        _client->login(userId);

    } else {
        createProfile(userId, userId);
        _client->setProfile(userId);
    }
}

void BackEnd::setReward(int revard) {

    if (_profile.record() < revard) {
        _profile.setRecord(revard);
        _client->updateProfile(_profile);
        _recordsTable->updateSourceItem(_dataConverter->toUserPreview(_profile));

    }
}

void BackEnd::setFog(bool fog) {
    if (_settingsData.fog == fog)
        return;

    _settingsData.fog = fog;
    _settings->setValue(FOG, fog);

    if (!_settingsData.fog)
        setFogAnimation(_settingsData.fog);

    emit fogChanged(_settingsData.fog);
}

void BackEnd::setFogAnimation(bool fogAnimation) {
    if (_settingsData.fogAnimation == fogAnimation ||
            !_settingsData.fog)
        return;

    _settingsData.fogAnimation = fogAnimation;
    _settings->setValue(FOG_ANIMATION, fogAnimation);

    emit fogAnimationChanged(_settingsData.fogAnimation);
}

void BackEnd::setGameState(GameState *gameState) {
    if (_profile.gameState() == gameState)
        return;

    _profile.setGameState(*gameState);
    emit gameStateChanged(gameState);
}

void BackEnd::setOnlineStatus(QH::ClientStatus onlineStatus) {
    if (_onlineStatus == static_cast<OnlineStatus>(onlineStatus))
        return;

    if (_profile.isOnline() && onlineStatus == QH::ClientStatus::Connected) {
        if (!_client->login(DataConverter::toUserMember(_profile))) {
            QuasarAppUtils::Params::log("Fail to login.", QuasarAppUtils::Error);
        }
    }

    if (_profile.isOnline() && onlineStatus == QH::ClientStatus::Logined) {
        if (!_client->subscribeToWorld()) {
            QuasarAppUtils::Params::log("Fail to subscribe to world.", QuasarAppUtils::Error);
        }
    }

    _onlineStatus = static_cast<OnlineStatus>(onlineStatus);
    emit onlineStatusChanged(static_cast<int>(_onlineStatus));
}
