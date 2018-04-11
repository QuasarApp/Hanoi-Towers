#include <QApplication>
//#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "backEnd.h"
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    translator.load(QString(":/languages/%0").arg(defaultLocale));
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    qmlRegisterType<BackEnd>("BackEnd",1,0,"BackEnd");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
