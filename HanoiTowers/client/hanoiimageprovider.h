/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef HANOIIMAGEPROVIDER_H
#define HANOIIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QRunnable>

class QThreadPool;
class HanoiClient;

class AsyncImageResponse : public QQuickImageResponse, public QRunnable
{
    public:
        AsyncImageResponse(const QString &id, const QSize &requestedSize, const HanoiClient *client);

        QQuickTextureFactory *textureFactory() const override;

        void run() override;

        QString m_id;
        QSize m_requestedSize;
        QQuickTextureFactory *m_texture;

private:
        const HanoiClient *_client = nullptr;
};


class HanoiImageProvider: public QQuickAsyncImageProvider
{
public:
    HanoiImageProvider(const HanoiClient* client);
    void stop();
    ~HanoiImageProvider() override;

    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &requestedSize) override;

private:
    QThreadPool *_pool = nullptr;
    const HanoiClient *_client = nullptr;
};

#endif // HANOIIMAGEPROVIDER_H
