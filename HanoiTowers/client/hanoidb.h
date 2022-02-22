#ifndef HANOIDB_H
#define HANOIDB_H

#include <database.h>

namespace QH {
class ISqlDBCache;
}

class HanoiDB: public QH::DataBase
{
    Q_OBJECT
public:
    HanoiDB();

    QH::ISqlDBCache * rawDb() const;
    // DataBase interface
protected:
    QStringList SQLSources() const override;
    bool upgradeDataBase() override;
};

#endif // HANOIDB_H
