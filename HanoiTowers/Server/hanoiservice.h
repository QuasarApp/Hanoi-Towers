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

    void handleReceive(const QList<Patronum::Feature> &data) override;
    QList<Patronum::Feature> supportedFeatures() override;

private:

    HanoiServer *_server = nullptr;

};

#endif // HANOISERVICE_H
