#ifndef SAVER_H
#define SAVER_H
#include <QObject>
#include <QFile>
#define SAVE "save"
class BackEnd: public QObject
{
    Q_OBJECT
    Q_PROPERTY(short reed READ read WRITE save)
    Q_PROPERTY(bool isFirst READ isFirst WRITE setShowHelp NOTIFY isFirstChanged)

private:

    void readCnfig();
    void writeConfig()const;
    bool isFirstStart;
    unsigned short lvl;
public:
    BackEnd();
    ~BackEnd();
public slots:
    /**
     * @brief save new lvl
     * @param lvl
     */
    void save(const short &lvl);

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
     * @brief read
     * @return curent lvl
     */
    short read()const;

signals:
    void isFirstChanged();
};

#endif // SAVER_H
