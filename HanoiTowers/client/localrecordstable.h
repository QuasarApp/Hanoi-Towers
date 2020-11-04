#ifndef LOCALRECORDSTABLE_H
#define LOCALRECORDSTABLE_H

#include "userpreview.h"

#include <dbobjectset.h>

class LocalRecordsTable: public QH::PKG::DBObjectSet
{
public:
    LocalRecordsTable();

    bool fromSqlRecord(const QSqlRecord &q) override;
    QH::PKG::DBObject *createDBObject() const override;

    const QMap<QString, UserPreview>& data() const;
    void setData(const QMap<QString, UserPreview> &data);
    void clear() override;
    bool isValid() const override;

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QString condition() const override;

private:
    QMap<QString, UserPreview> _data;
};

#endif // LOCALRECORDSTABLE_H
