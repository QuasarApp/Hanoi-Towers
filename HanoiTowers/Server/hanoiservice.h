#ifndef HANOISERVICE_H
#define HANOISERVICE_H

#include <QCoreApplication>
#include <patronum.h>

class HanoiServer;

class HanoiService : public Patronum::Service<QCoreApplication>
{
public:
    HanoiService(int argc, char *argv[]);
    ~HanoiService();

    // QtServiceBase interface
protected:
    void onStart() override;
    void onStop() override;

    bool handleReceive(const Patronum::Feature &data) override;
    QSet<Patronum::Feature> supportedFeatures() override;

private:
    bool changeFileLogPath(const QString &path);

    HanoiServer *_server = nullptr;

};

#endif // HANOISERVICE_H
