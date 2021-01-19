#ifndef USERAVATAR_H
#define USERAVATAR_H

#include <dbobject.h>

class UserAvatar: public QH::PKG::DBObject
{
public:
    UserAvatar();
    bool copyFrom(const QH::PKG::AbstractData *other) override;
    QH::PKG::DBObject *createDBObject() const override;
    bool fromSqlRecord(const QSqlRecord &q) override;
    bool isValid() const override;

    // StreamBase interface
    QByteArray image() const;
    void setImage(const QByteArray &image);

    QString userId() const;
    void setUserId(const QString &userId);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    QH::PKG::DBVariantMap variantMap() const override;
    QString primaryKey() const override;

private:
    QByteArray _image;
    QString _userId;

};

#endif // USERAVATAR_H
