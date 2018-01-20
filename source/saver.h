#ifndef SAVER_H
#define SAVER_H
#include <QObject>
#include <QFile>
#define SAVE "save"
class Saver: public QObject
{
    Q_OBJECT
    Q_PROPERTY(short reed READ read WRITE save)
public:
    Saver();
public slots:
    void save(const short &lvl)const;
    short read()const;
};

#endif // SAVER_H
