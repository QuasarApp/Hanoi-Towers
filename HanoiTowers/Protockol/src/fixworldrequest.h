#ifndef FIXWORLDREQUEST_H
#define FIXWORLDREQUEST_H

#include <abstractdata.h>

class FixWorldRequest: public QH::PKG::AbstractData
{
public:
    FixWorldRequest();
    bool isValid() const override;

    // StreamBase interface
    unsigned int worldVersion() const;
    void setWorldVersion(unsigned int worldVersion);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

private:
    unsigned int _worldVersion = 0;

};

#endif // FIXWORLDREQUEST_H
