#include <QGuiApplication>
#include <QFont>
#include <QFontDatabase>
#include <iostream>
//#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "backEnd.h"
#include <QTranslator>
#include <qmlnotifyservice.h>

void setFont(const QGuiApplication& app){

    QString fontPath = "://ubuntu";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
        app.setFont(font);
    }
}

bool initLocale(const QString &locale, QGuiApplication& app, QTranslator &translator){

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!locale.isEmpty() && translator.load(QString(":/languages/%0").arg(locale))){
        return app.installTranslator(&translator);
    }

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }

    return app.installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // <--
    QGuiApplication::setApplicationName("HanoiTowers"); // <--
    QGuiApplication::setOrganizationName("QuasarApp"); // <--
    QGuiApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--

    QGuiApplication app(argc, argv);
    setFont(app);

    QTranslator translator;

    QString locale = "";

    if(argc > 1) {
        locale = QString::fromLatin1(argv[1]);
    }

    if(!initLocale(locale, app, translator)){
        std::cout << "error load language : " << locale.toStdString() <<std::endl;
    }

    QQmlApplicationEngine engine;
//    qmlRegisterType<BackEnd>("BackEnd",1,0,"BackEnd");
    BackEnd back;
    auto root = engine.rootContext();

    if (!QmlNotificationService::init(&engine)) {
        return 1;
    }

    root->setContextProperty("backEnd", &back);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
