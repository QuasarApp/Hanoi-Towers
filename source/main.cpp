#include <QApplication>
//#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "saver.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // app.primaryScreen()->setOrientationUpdateMask(Qt::LandscapeOrientation);
    QQmlApplicationEngine engine;
    qmlRegisterType<Saver>("Saver",1,0,"Saver");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
