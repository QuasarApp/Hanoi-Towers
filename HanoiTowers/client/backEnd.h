/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef SAVER_H
#define SAVER_H
#include "gamestate.h"
#include "hanoiclient.h"
#include "localuser.h"
#include "profiledata.h"
#include "settingsdata.h"
#include <quasarapp.h>
#include <QObject>
#include <QFile>
#include "onlinestatusqml.h"
//#include <listviewmodel.h>

#define SAVE "data"

#define MAIN_FOLDER                 QDir::homePath() + "/.HanoiTowers"
#define MAIN_FOLDER_KEY             "HanoiTowersFolder"
#define MAIN_SETINGS_FILE           MAIN_FOLDER + "/" + SAVE

namespace LoginView {
class LVMainModel;
class UserData;
}
class QQmlApplicationEngine;
class RecordListModel;
class HanoiImageProvider;
class DataConverter;
class RecordsProxyModel;

class BackEnd: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool randomColor READ randomColor WRITE setRandomColor NOTIFY randomColorChanged)
    Q_PROPERTY(bool animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(bool fog READ fog WRITE setFog NOTIFY fogChanged)
    Q_PROPERTY(bool fogAnimation READ fogAnimation WRITE setFogAnimation NOTIFY fogAnimationChanged)

    Q_PROPERTY(GameState* gameState READ gameState WRITE setGameState NOTIFY profileChanged)
    Q_PROPERTY(QObject* client READ client)

    // local
    Q_PROPERTY(QObject* profileList READ profileList  NOTIFY profileListChanged)
    Q_PROPERTY(QObject* profileObject READ profileObject  NOTIFY profileChanged)

    // global
    Q_PROPERTY(QObject* worldList READ worldList  NOTIFY worldListChanged)
    Q_PROPERTY(QObject* bestUser READ bestUser  NOTIFY bestUserChanged)
    Q_PROPERTY(QObject* selectedUser READ selectedUser  NOTIFY selectedUserChanged)

    Q_PROPERTY(QString profile READ profile WRITE setProfile NOTIFY profileChanged)
    Q_PROPERTY(int onlineStatus READ onlineStatus NOTIFY onlineStatusChanged)



public:
    BackEnd(QQmlApplicationEngine *engine);
    ~BackEnd();

    Q_INVOKABLE QString profile() const;
    Q_INVOKABLE QObject* profileList();
    Q_INVOKABLE QObject* worldList();

    Q_INVOKABLE bool createProfile(const QString &userId, const QString& userName);

    /**
     * @brief isFirst
     * @return true if is first start
     */
    Q_INVOKABLE bool isFirst()const;

    /**
     * @brief setShowHelp set new state for show help message
     * @param state - a new state of show help message
     */
    Q_INVOKABLE void setShowHelp(bool state);

    /**
     * @brief setNewAvatar This method sets new avatar for current user.
     * @param pathToAvatar
     */
    Q_INVOKABLE void setNewAvatar(QString pathToAvatar);

    /**
     * @brief selectUserFromWorldTable This method changes selectedUser object.
     * @param userId
     */
    Q_INVOKABLE void selectUserFromWorldTable(const QString &userId);

    bool fog() const;

    bool fogAnimation() const;

    Q_INVOKABLE void onlineRequest(const QString& userId);

    int onlineStatus() const;

    QObject *bestUser();
    QObject *selectedUser();

public slots:

    /**
     * @brief getMinSteps
     * @param lvl
     * @return minimum step of current lvl
     */
    unsigned short getMinSteps(const unsigned short lvl) const;

    /**
     * @brief randomColor
     * @return return true if enable random color of plate;
     */
    bool randomColor()const;

    /**
     * @brief animation
     * @return name of render animation;
     */
    bool animation() const;

    /**
     * @brief setAnimation
     * @param name of new animation;
     */
    void setAnimation(bool valeu);

    /**
     * @brief setRandomColor
     * enabfle or disable random colors.
     */
    void setRandomColor(bool );

    /**
     * @brief gameState
     * @return
     */
    GameState* gameState();

    /**
     * @brief client
     * @return
     */
    QObject *client();

    /**
     * @brief profileObject
     * @return
     */
    QObject* profileObject();

    void removeUser(const QString &userId);
    void setProfile(QString userId);
    void setReward(int);
    void setFog(bool fog);
    void setFogAnimation(bool fogAnimation);

    void setGameState(GameState* gameState);



signals:
    void animationChanged();
    void randomColorChanged();
    void profileListChanged();
    void profileChanged();

    void usersListModelChanged(QObject* usersListModel);
    void showOnlinePage();


    void fogChanged(bool fog);

    void fogAnimationChanged(bool fogAnimation);

    void onlineStatusChanged(int onlineStatus);

    void worldListChanged(QObject* worldList);

    void bestUserChanged(QObject* bestUser);

    void selectedUserChanged(QObject* selectedUser);

private slots:
    void handleChangeName(const QString&);
    void handleBestUserIdChanged(const QString&userId);

    void handleCreateNewProfile(const LoginView::UserData&);
    void handleOnlineRequest(const LoginView::UserData&);
    void handleOnlineRegisterRequest(const LoginView::UserData&);

    void handleOnlineRequestError(QH::ErrorCodes::Code, const QString&Errr);

    void handleAcceptUserData(QSharedPointer<LocalUser> profileId);
    void setOnlineStatus(QH::ClientStatus onlineStatus);
    void handleWorldChanged(QSharedPointer<WorldUpdate>);
    void handleWorldInited(QHash<QString, UserPreview> initWorldList);

private:
    void init();

    QuasarAppUtils::Settings *_settings = nullptr;

    LoginView::LVMainModel *_loginModel = nullptr;
    LoginView::LVMainModel *_createNewOfflineUser = nullptr;

    RecordListModel * _recordsTable = nullptr;
    RecordListModel * _world = nullptr;
    RecordsProxyModel * _worldProxy = nullptr;

    LocalUser _profile;
    LocalUser _bestUser;
    LocalUser _selectedUser;


    HanoiClient *_client = nullptr;

    SettingsData _settingsData;
    HanoiImageProvider *_imageProvider = nullptr;
    DataConverter *_dataConverter = nullptr;
    OnlineStatus _onlineStatus = OnlineStatus::Dissconnected;
};



#endif // SAVER_H
