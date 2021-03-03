#include "world.h"
#include "worldupdate.h"

World::World(const QString &worldName):
QH::PKG::DBObjectSet("UsersData") {
    _subscribeId = qHash(worldName);
}

bool World::fromSqlRecord(const QSqlRecord &q) {
    UserPreview data;
    data.id = q.value("userID").toString();

    data.userName = q.value("userName").toString();
    data.record = q.value("points").toInt();

    _data.insert(data);

    return true;
}

QH::PKG::DBObject *World::createDBObject() const {
    return create<World>();
}

void World::clear() {
    _data.clear();
}

bool World::isValid() const {
    return true;
}

const QH::AccessToken &World::getSignToken() const {
    return _token;
}

unsigned int World::subscribeId() const {
    return _subscribeId;
}

QH::PKG::DBVariantMap World::variantMap() const {
    return {{"id",          {}},
            {"points",      {}},
            {"userName",    {}}};
}

QString World::condition() const {
    return "";
}

QDataStream &World::fromStream(QDataStream &stream) {
    DBObjectSet::fromStream(stream);

    stream >> _data;
    stream >> _token;
    stream >> _subscribeId;
    stream >> _worldVersion;
    stream >> _bestUserId;

    return stream;
}

QDataStream &World::toStream(QDataStream &stream) const {
    DBObjectSet::toStream(stream);

    stream << _data;
    stream << _token;
    stream << _subscribeId;
    stream << _worldVersion;
    stream << _bestUserId;

    return stream;
}

bool World::softUpdate(const WorldUpdate &update) {

    const auto &val =  update.getDataAddUpdate();

    auto it = _data.find(UserPreview(_bestUserId));
    int bestRecord = 0;
    if (it != _data.end()) {
        bestRecord = (*it).record;
    }

    for (const auto &item : val) {
        if (item.record >= bestRecord) {
            bestRecord = item.record;
            _bestUserId = item.id;
        }
    }

    _data -= update.getDataRemove();

    return true;
}

bool World::hardUpdate(const WorldUpdate &update) {

    _data += update.getDataAddUpdate();
    _data -= update.getDataRemove();

    if (_data.size()) {
        _bestUserId = fullSearch()->id;
    }

    return true;
}

QSet<UserPreview>::ConstIterator World::fullSearch() const {
    auto lessThen = [](const UserPreview & left, const UserPreview &right) {
        return left.record <= right.record;
    };
    return std::max_element(_data.begin(), _data.end(), lessThen);
}

QString World::getBestUserId() const {
    return _bestUserId;
}

void World::setBestUserId(const QString &value) {
    _bestUserId = value;
}

unsigned int World::getWorldVersion() const {
    return _worldVersion;
}

QSet<UserPreview> World::getData() const {
    return _data;
}

void World::setData(const QSet<UserPreview> &data) {
    _data = data;
}

bool World::applyUpdate(const WorldUpdate &update) {

    if (update.getWorldVersion() != _worldVersion + 1) {
        return false;
    }
    auto oldBestUser = UserPreview{_bestUserId};
    if (update.getDataRemove().contains(oldBestUser) ||
        update.getDataAddUpdate().contains(oldBestUser)) {

        hardUpdate(update);
    } else {
        softUpdate(update);
    }

    _worldVersion++;

    return true;
}

void World::setToken(const QH::AccessToken &token) {
    _token = token;
}
