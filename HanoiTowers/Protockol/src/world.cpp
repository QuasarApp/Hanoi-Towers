#include "world.h"
#include "worldupdate.h"

World::World(const QString &worldName):
QH::PKG::DBObjectSet("UsersData") {
    _subscribeId = qHash(worldName);
}

bool World::fromSqlRecord(const QSqlRecord &q) {
    UserPreview data;
    data.id = q.value("id").toString();

    data.userName = q.value("userName").toString();
    data.record = q.value("points").toInt();

    softUpdatePrivate({data});

    return true;
}

QH::PKG::DBObject *World::createDBObject() const {
    return create<World>();
}

void World::clear() {
    _data.clear();
    setBestUserId("");
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

bool World::copyFrom(const QH::PKG::AbstractData *other) {
    copy<World>(*other);
    return isValid();
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

    QString bestId;
    stream >> bestId;
    setBestUserId(bestId);

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

void World::bestUserChanged(const QString&) {}

bool World::softUpdate(const WorldUpdate &update) {

    if (!softUpdatePrivate(update.getDataAddUpdate())) {
        return false;
    }

    _data -= update.getDataRemove();


    return true;
}

bool World::softUpdatePrivate(const QSet<UserPreview>& val) {

    QString bestid = getBestUserId();
    auto it = _data.find(UserPreview(bestid));
    int bestRecord = 0;
    if (it != _data.end()) {
        bestRecord = (*it).record;
    }

    bool userChanged = false;
    for (const auto &item : val) {
        if (item.record >= bestRecord) {
            bestRecord = item.record;
            bestid = item.id;
            userChanged = true;
        }
        _data += item;
    }

    if (userChanged) {
        setBestUserId(bestid);
    }

    return true;
}

bool World::hardUpdate(const WorldUpdate &update) {

    _data += update.getDataAddUpdate();
    _data -= update.getDataRemove();

    if (_data.size()) {
        QString newBest = fullSearch()->id;

        if (newBest != getBestUserId()) {
            setBestUserId(newBest);
        }
    }

    return true;
}

QSet<UserPreview>::ConstIterator World::fullSearch() const {
    auto lessThen = [](const UserPreview & left, const UserPreview &right) {
        return left.record <= right.record;
    };
    return std::max_element(_data.begin(), _data.end(), lessThen);
}

const QString& World::getBestUserId() const {
    return _bestUserId;
}

void World::setBestUserId(const QString &value) {
    if (_bestUserId != value) {

        _bestUserId = value;
        bestUserChanged(_bestUserId);
    }
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
    auto oldBestUser = UserPreview{getBestUserId()};
    if (update.getDataRemove().contains(oldBestUser) ||
        update.getDataAddUpdate().contains(oldBestUser)) {

        hardUpdate(update);
    } else {
        softUpdate(update);
    }

    _worldVersion++;

    return true;
}

void World::setSignToken(const QH::AccessToken &token) {
    _token = token;
}
