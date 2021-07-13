/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoitowers.h"
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
#include <worldupdate.h>
#include "dataconverter.h"
#include "localuser.h"
#include "recordsproxymodel.h"

#define DEFAULT_USER_ID "DefaultUser"
#define DEFAULT_USER_NAME "User"

#define FIRST_RUN_KEY "isFirstStart"
#define ANIMATION_KEY "animation"
#define RANDOM_COLOR_KEY "randomColor"
#define CURRENT_PROFILE_KEY "currentProfile"
#define FOG "fog"
#define FOG_ANIMATION "fogAnimation"
#define SHOW_CREDITS "showCredits"
#define LAUNCH_COUNT "launchCount"

HanoiTowers::HanoiTowers(QQmlApplicationEngine *engine):
    QObject(),
    _profile()
{
    _settings = QuasarAppUtils::Settings::instance();

    _client = new HanoiClient();
    _loginModel = new LoginView::LVMainModel("userLogin", this);
    _createNewOfflineUser = new LoginView::LVMainModel("createUser", this);

    _recordsTable   = new RecordListModel(this);
    _recordsTableProxy = new RecordsProxyModel(this);
    _world          = new RecordListModel(this);
    _worldProxy     = new RecordsProxyModel(this);

    _worldProxy->setSourceModel(_world);
    _worldProxy->setDynamicSortFilter(true);
    _worldProxy->setSortRole(RecordListModel::RecordListModelRoles::Record);
    _worldProxy->sort(0, Qt::SortOrder::DescendingOrder);

    _recordsTableProxy->setSourceModel(_recordsTable);
    _recordsTableProxy->setDynamicSortFilter(true);
    _recordsTableProxy->setSortRole(RecordListModel::RecordListModelRoles::Record);
    _recordsTableProxy->sort(0, Qt::SortOrder::DescendingOrder);

    _imageProvider = new HanoiImageProvider(_client->getUsersCache());
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
    _createNewOfflineUser->setAcceptButtonText(tr("Create"));
    _createNewOfflineUser->init(engine);

    _recordsTable->setSource(_client->localUsersPreview());

    engine->addImageProvider("HanoiImages", _imageProvider);


    connect(_loginModel, &LoginView::LVMainModel::sigLoginRequest,
            this, &HanoiTowers::handleOnlineRequest);

    connect(_loginModel, &LoginView::LVMainModel::sigRegisterRequest,
            this, &HanoiTowers::handleOnlineRegisterRequest);

    connect(_createNewOfflineUser , &LoginView::LVMainModel::sigRegisterRequest,
            this, &HanoiTowers::handleCreateNewProfile);

    connect(_client, &HanoiClient::requestError,
            this, &HanoiTowers::handleOnlineRequestError);

    connect(_client, &HanoiClient::userDataChanged,
            this, &HanoiTowers::handleAcceptUserData);

    connect(_client, &HanoiClient::statusChanged,
            this, &HanoiTowers::setOnlineStatus);

    connect(_client, &HanoiClient::worldChanged,
            this, &HanoiTowers::handleWorldChanged);

    connect(_client, &HanoiClient::worldInited,
            this, &HanoiTowers::handleWorldInited);

    connect(_client, &HanoiClient::sigBestuserIdChanged,
            this, &HanoiTowers::handleBestUserIdChanged);

    connect(&_profile, &LocalUser::nameChanged,
            this, &HanoiTowers::handleChangeName);

    setProfile(_settings->getStrValue(CURRENT_PROFILE_KEY, DEFAULT_USER_ID));
    init();
}

void HanoiTowers::init() {
    _settingsData.animation = _settings->getValue(ANIMATION_KEY, true).toBool();
    _settingsData.randomColor = _settings->getValue(RANDOM_COLOR_KEY, false).toBool();
    _settingsData.fog = _settings->getValue(FOG, true).toBool();
    _settingsData.fogAnimation = _settings->getValue(FOG_ANIMATION, true).toBool();
    _settingsData.showCredits = _settings->getValue(SHOW_CREDITS, true).toBool();
    _settingsData._launchCount = _settings->getValue(LAUNCH_COUNT, 0).toUInt();

    setLaunchCount(_settingsData._launchCount + 1);

}

void HanoiTowers::loadOldSaves() {
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
        if (lvl < 99)
            gameState()->saveLvl(lvl);


        f.close();
        QFile::remove(MAIN_SETINGS_FILE);

        updateProfile();
    }
}

void HanoiTowers::onlineRequest(const QString &userId) {

    if (_client->isLogined()) {
        return;
    }

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

void HanoiTowers::updateProfile() {
    if (!_profile.isValid())
        return;

    if (!_client->updateProfile(_profile)) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Update Profile error"),
                    tr("Failed to update yuo user data"
                       " please check network connection befor update prifile"), "",
                    QmlNotificationService::NotificationData::Error);
    } else {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Update Profile"),
                    tr("User data updated successful"), "",
                    QmlNotificationService::NotificationData::Normal);
    }
}

int HanoiTowers::onlineStatus() const {
    return static_cast<int>(_onlineStatus);
}

QString HanoiTowers::onlineStatusColor() const {
    switch (_onlineStatus) {
    case OnlineStatus::Connected:
    case OnlineStatus::Connecting: {
        return "#ffaa7f";
    }
    case OnlineStatus::Loginning:
    case OnlineStatus::Logined: {
        return "#00ff7f";
    }
    default: return "#787878";
    }
}

QObject *HanoiTowers::bestUser() {
    return &_bestUser;
}

QObject *HanoiTowers::selectedUser() {
    return &_selectedUser;
}

bool HanoiTowers::isAndroid() const{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool HanoiTowers::isAdMod() const {
#ifdef HANOI_ADMOD
    return true;
#else
    return false;
#endif
}

void HanoiTowers::handleChangeName(const QString &) {
    emit profileChanged();
}

void HanoiTowers::handleBestUserIdChanged(const QString & userId) {
    _bestUser.setId(userId);
}

void HanoiTowers::handleCreateNewProfile(const LoginView::UserData & data) {
    createProfile(data.nickname(), data.nickname());
}

void HanoiTowers::handleOnlineRequest(const LoginView::UserData & user) {

    if (!_client->login(user.nickname(), user.rawPassword())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("login error"),
                    tr("Failed to login into online account,"
                       " please check your password and username"), "",
                    QmlNotificationService::NotificationData::Error);

    }
}

void HanoiTowers::handleOnlineRegisterRequest(const LoginView::UserData &user) {
    if (!_client->signup(user.nickname(), user.rawPassword())) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Register online error"),
                    tr("Failed to register this account,"
                       " if this account was created by you, try to restore it."), "",
                    QmlNotificationService::NotificationData::Error);
    }
}

void HanoiTowers::handleOnlineRequestError(QH::ErrorCodes::Code code, const QString & err) {

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

void HanoiTowers::handleAcceptUserData(QSharedPointer<LocalUser> data) {
    if (_profile.getId() == data->getId()) {

        _profile.copyFrom(data.data());
        _settings->setValue(CURRENT_PROFILE_KEY, _profile.getId());

        loadOldSaves();

        if (data->gameState()->lvl() < 15) {
            data->gameState()->saveLvl(15);
        }

        updateProfile();

        emit profileChanged();

    }

    if (_bestUser.getId() == data->getId()) {
        _bestUser.copyFrom(data.data());
        emit bestUserChanged(&_bestUser);

    }

    if (_selectedUser.getId() == data->getId()) {
        _selectedUser.copyFrom(data.data());
        emit selectedUserChanged(&_selectedUser);

    }
}

bool HanoiTowers::randomColor() const {
    return _settings->getValue(RANDOM_COLOR_KEY, false).toBool();
}

void HanoiTowers::setRandomColor(bool random) {

    if (_settingsData.randomColor != random) {

        _settings->setValue(RANDOM_COLOR_KEY, random);
        _settingsData.randomColor = random;
        emit randomColorChanged();
    }
}

bool HanoiTowers::animation() const{
    return _settings->getValue(ANIMATION_KEY, true).toBool();
}

void HanoiTowers::setAnimation(bool value) {
    if (_settingsData.animation != value) {

        _settings->setValue(ANIMATION_KEY, value);
        _settingsData.animation = value;
        emit animationChanged();
    }
}

unsigned short HanoiTowers::getMinSteps(const unsigned short lvl) const{
    return static_cast<unsigned short>(pow(2, lvl)) - 1;
}

bool HanoiTowers::isFirst()const{
    return _settings->getValue(FIRST_RUN_KEY, true).toBool();
}

void HanoiTowers::setShowHelp(bool state) {
    _settings->setValue(FIRST_RUN_KEY, state);
}

void HanoiTowers::setNewAvatar(QString pathToAvatar) {
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

    _client->setNewAvatar(_profile.getId().toString(), arr);

}

void HanoiTowers::selectUserFromWorldTable(const QString &userId) {
    _selectedUser.setId(userId);
    _client->getUserData(userId);
}

bool HanoiTowers::fog() const {
    return _settings->getValue(FOG, true).toBool();
}

bool HanoiTowers::fogAnimation() const {
    return _settings->getValue(FOG_ANIMATION, true).toBool();
}

HanoiTowers::~HanoiTowers() {
    updateProfile();

    QCoreApplication::processEvents();

    _imageProvider->stop();
    _client->softDelete();


    delete _dataConverter;
}

QString HanoiTowers::profile() const {
    return _profile.name();
}

QObject* HanoiTowers::profileList() {
    return _recordsTableProxy;
}

QObject *HanoiTowers::worldList() {
    return _worldProxy;
}

bool HanoiTowers::createProfile(const QString& userId, const QString &userName) {

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

    _recordsTable->updateAddSourceItem(_dataConverter->toUserPreview(user));

    return true;
}

QObject *HanoiTowers::profileObject() {
    return &_profile;
}

GameState *HanoiTowers::gameState() {
    if (auto obj = dynamic_cast<LocalUser*>(profileObject())) {
        return obj->gameState();
    }

    return nullptr;
}

QObject *HanoiTowers::client() {
    return _client;
}

void HanoiTowers::removeUser(const QString &userId) {

    if (_client->isLogined() && !_client->removeUser()) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Remove online error"), tr("current profile not online!"), "",
                    QmlNotificationService::NotificationData::Warning);
    }

    if (!_client->removeLocalUser(userId)) {
        QmlNotificationService::NotificationService::getService()->setNotify(
                    tr("Remove Local user"), tr("Failed to remove the local user data"), "",
                    QmlNotificationService::NotificationData::Warning);
        return;
    }

    _recordsTable->removeSourceItem(userId);

    auto userID = _recordsTable->data(_recordsTable->index(0,0), RecordListModel::UserId).toString();

    if (userID.isEmpty()) {
        userID = DEFAULT_USER_ID;
    }

    setProfile(userID);

}

void HanoiTowers::setProfile(QString userId) {
    if (!_client)
        return;

    updateProfile();

    _profile.setId(userId);
    if (_client->setProfile(userId)) {
        emit profileChanged();

    } else {
        createProfile(userId, userId);
        _client->setProfile(userId);
    }
}

void HanoiTowers::setReward(int revard) {

    if (_profile.record() < revard) {
        _profile.setRecord(revard);
        updateProfile();
        _recordsTable->updateAddSourceItem(_dataConverter->toUserPreview(_profile));

    }
}

void HanoiTowers::setFog(bool fog) {
    if (_settingsData.fog == fog)
        return;

    _settingsData.fog = fog;
    _settings->setValue(FOG, fog);

    if (!_settingsData.fog)
        setFogAnimation(_settingsData.fog);

    emit fogChanged(_settingsData.fog);
}

void HanoiTowers::setFogAnimation(bool fogAnimation) {
    if (_settingsData.fogAnimation == fogAnimation ||
            !_settingsData.fog)
        return;

    _settingsData.fogAnimation = fogAnimation;
    _settings->setValue(FOG_ANIMATION, fogAnimation);

    emit fogAnimationChanged(_settingsData.fogAnimation);
}

void HanoiTowers::setGameState(GameState *gameState) {
    if (_profile.gameState() == gameState)
        return;

    _profile.setGameState(*gameState);
    emit profileChanged();
}

void HanoiTowers::setOnlineStatus(QH::ClientStatus onlineStatus) {
    if (_onlineStatus == static_cast<OnlineStatus>(onlineStatus))
        return;

    if (_profile.isOnline() && onlineStatus == QH::ClientStatus::Connected) {
        if (!_client->login(DataConverter::toUserMember(_profile))) {
            QuasarAppUtils::Params::log("Failed to login.", QuasarAppUtils::Error);
        }
    }

    if (_profile.isOnline() && onlineStatus == QH::ClientStatus::Logined) {
        if (!_client->getUserData(_profile.getId().toString())) {
            QuasarAppUtils::Params::log("Failed to send a user data request.", QuasarAppUtils::Error);
        }

        if (!_client->subscribeToWorld()) {
            QuasarAppUtils::Params::log("Failed to subscribe to world.", QuasarAppUtils::Error);
        }
    }

    _onlineStatus = static_cast<OnlineStatus>(onlineStatus);
    emit onlineStatusChanged(static_cast<int>(_onlineStatus));
}

void HanoiTowers::handleWorldChanged(QSharedPointer<WorldUpdate> delta) {
    for (const auto &val: qAsConst(delta->getDataAddUpdate())) {
        _world->updateAddSourceItem(val);
    }

    for (const auto &val: qAsConst(delta->getDataRemove())) {
        _world->removeSourceItem(val);
    }
}

void HanoiTowers::handleWorldInited(QHash<QString, UserPreview> initWorldList) {
    _world->setSource({initWorldList.begin(), initWorldList.end()});
}

bool HanoiTowers::showCredits() const {
    return _settingsData.showCredits;
}

void HanoiTowers::setShowCredits(bool newShowCredits) {
    if (_settingsData.showCredits != newShowCredits) {

        _settings->setValue(SHOW_CREDITS, newShowCredits);
        _settingsData.showCredits = newShowCredits;
        emit showCreditsChanged();
    }
}

unsigned int HanoiTowers::launchCount() const {
    return _settingsData._launchCount;
}

void HanoiTowers::setLaunchCount(unsigned int newLaunchCount) {
    if (_settingsData._launchCount == newLaunchCount)
        return;

    _settingsData._launchCount = newLaunchCount;
    _settings->setValue(LAUNCH_COUNT, newLaunchCount);

    emit launchCountChanged();
}
