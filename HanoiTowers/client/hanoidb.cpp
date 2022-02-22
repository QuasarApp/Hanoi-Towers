#include "hanoidb.h"

HanoiDB::HanoiDB()
{

}

QH::ISqlDBCache *HanoiDB::rawDb() const{
    return db();
}

QStringList HanoiDB::SQLSources() const {
    return {
        ":/sql/sql/database.sql"
    };
}

bool HanoiDB::upgradeDataBase() {
    return true;
}
