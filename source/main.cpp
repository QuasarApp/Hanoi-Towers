#include <QApplication>
//#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "backEnd.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // app.primaryScreen()->setOrientationUpdateMask(Qt::LandscapeOrientation);
    QQmlApplicationEngine engine;
    qmlRegisterType<BackEnd>("BackEnd",1,0,"BackEnd");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
