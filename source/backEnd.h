#ifndef SAVER_H
#define SAVER_H
#include <QObject>
#include <QFile>
#define SAVE "save"
class BackEnd: public QObject
{
    Q_OBJECT
    Q_PROPERTY(short reed READ read WRITE save)
private:

public:
    BackEnd();
public slots:
    void save(const short &lvl)const;
    unsigned short getMinSteps(const unsigned short lvl)const;
    short read()const;
};

#endif // SAVER_H
