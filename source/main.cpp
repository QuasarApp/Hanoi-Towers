#include <QApplication>
#include <QFont>
#include <QFontDatabase>
//#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "backEnd.h"
#include <QTranslator>


void setFont(const QApplication& app){

    QString fontPath = "://ubuntu";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
        app.setFont(font);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setFont(app);

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
