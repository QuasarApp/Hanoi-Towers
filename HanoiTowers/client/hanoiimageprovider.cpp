#include "hanoiclient.h"
#include "hanoiimageprovider.h"

#include <QThread>
#include <QThreadPool>

HanoiImageProvider::HanoiImageProvider(const HanoiClient *client) {
    _pool = new QThreadPool();
    _client = client;
}

HanoiImageProvider::~HanoiImageProvider() {
    _pool->deleteLater();
}

QQuickImageResponse *HanoiImageProvider::requestImageResponse(const QString &id,
                                                              const QSize &requestedSize) {

    AsyncImageResponse *response = new AsyncImageResponse(id, requestedSize, _client);
    _pool->start(response);
    return response;

}

AsyncImageResponse::AsyncImageResponse(const QString &id, const QSize &requestedSize,
                                       const HanoiClient *client)
    : m_id(id), m_requestedSize(requestedSize), m_texture(0), _client(client) {
    setAutoDelete(false);
}

QQuickTextureFactory *AsyncImageResponse::textureFactory() const {
    return m_texture;
}

void AsyncImageResponse::run() {

    QImage image = _client->userAvatar(m_id.toLocal8Bit());;

    if (image.isNull()) {
        image = QImage(":/img/DefaultAvatar");
    }

    if (m_requestedSize.isValid())
        image = image.scaled(m_requestedSize);

    m_texture = QQuickTextureFactory::textureFactoryForImage(image);
    emit finished();
}
