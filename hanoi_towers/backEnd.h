#ifndef SAVER_H
#define SAVER_H
#include "gamestate.h"
#include <quasarapp.h>
#include <QObject>
#include <QFile>
#define SAVE "data"

#define MAIN_FOLDER                 QDir::homePath() + "/.HanoiTowers"
#define MAIN_FOLDER_KEY             "HanoiTowersFolder"
#define MAIN_SETINGS_FILE             MAIN_FOLDER + "/" + SAVE

class BackEnd: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isFirst READ isFirst WRITE setShowHelp NOTIFY firstChanged)
    Q_PROPERTY(bool randomColor READ randomColor WRITE setRandomColor NOTIFY randomColorChanged)
    Q_PROPERTY(bool animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(QObject* gameState READ gameState)

    Q_PROPERTY(QStringList profileList READ profileList WRITE setProfileList NOTIFY profileListChanged)
    Q_PROPERTY(int profileIndex READ profileIndex NOTIFY profileIndexChanged)
    Q_PROPERTY(QString profile READ profile NOTIFY profileIndexChanged)


private:

    void readCnfig();
    void writeConfig()const;

    QuasarAppUtils::Settings *_settings = nullptr;
    GameState *_gameState = nullptr;

    QStringList _localProfilesList;
    int _profileIndex;

public:
    BackEnd();
    ~BackEnd();

    QString profile() const;

    QStringList profileList() const;

    int profileIndex() const;

public slots:

    /**
     * @brief save new lvl
     * @param lvl
     */
    void save(short lvl);

    /**
     * @brief getMinSteps
     * @param lvl
     * @return minimum step of current lvl
     */
    unsigned short getMinSteps(const unsigned short lvl) const;

    /**
     * @brief isFirst
     * @return true if is first start
     */
    bool isFirst()const;

    /**
     * @brief setShowHelp set new state for show help message
     * @param state - a new state of show help message
     */
    void setShowHelp(bool state);

    /**
     * @brief reset all config to default values.
     */
    void reset();

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
    void setAnimation(bool name);

    /**
     * @brief setRandomColor
     * enabfle or disable random colors.
     */
    void setRandomColor(bool );

    /**
     * @brief read
     * @return curent lvl
     */
    short read()const;

    QObject *gameState();
    void setProfileList(QStringList profileList);

signals:
    void firstChanged();
    void animationChanged();
    void randomColorChanged();
    void profileListChanged(QStringList profileList);
    void profileIndexChanged(int profileIndex);
};

#endif // SAVER_H
