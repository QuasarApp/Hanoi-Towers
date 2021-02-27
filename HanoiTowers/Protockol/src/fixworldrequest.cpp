#include "fixworldrequest.h"

FixWorldRequest::FixWorldRequest() {

}

bool FixWorldRequest::isValid() const {
    return QH::PKG::AbstractData::isValid() && _worldVersion;
}

QDataStream &FixWorldRequest::fromStream(QDataStream &stream) {
    AbstractData::fromStream(stream);

    stream >> _worldVersion;

    return stream;
}

QDataStream &FixWorldRequest::toStream(QDataStream &stream) const {
    AbstractData::toStream(stream);

    stream << _worldVersion;
    return stream;

}

unsigned int FixWorldRequest::worldVersion() const {
    return _worldVersion;
}

void FixWorldRequest::setWorldVersion(unsigned int worldVersion) {
    _worldVersion = worldVersion;
}
