#include <QApplication>
//#include <QScreen>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // app.primaryScreen()->setOrientationUpdateMask(Qt::LandscapeOrientation);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
