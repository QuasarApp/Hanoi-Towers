#ifndef WORLDCLIENT_H
#define WORLDCLIENT_H

#include <world.h>


class WorldClient:  public QObject, public World
{
    Q_OBJECT
public:
    WorldClient(const QString& worldName = "World");

signals:
    void sigBestUserChanged(QString bestUser);


    // World interface
protected:
    void bestUserChanged(const QString &bestUser) override;
};

#endif // WORLDCLIENT_H
