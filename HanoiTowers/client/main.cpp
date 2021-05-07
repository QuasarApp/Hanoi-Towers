/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include <QGuiApplication>
#include <QFont>
#include <QFontDatabase>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "activityhandler.h"
#include "hanoitowers.h"
#include <QTranslator>
#include <qmlnotifyservice.h>
#include <credits.h>


int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("HanoiTowers"); // <--
    QGuiApplication::setOrganizationName("QuasarApp"); // <--
    QGuiApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--

    QGuiApplication app(argc, argv);

    QLocale locale = QLocale::system();

    if(argc > 1) {
        locale = QLocale(QString::fromLatin1(argv[1]));
    }

    if(!QuasarAppUtils::Locales::init(locale, {":/languages/languages/",
                                               ":/credits_languages/",
                                               ":/qmlNotify_languages/",
                                               ":/lv_languages/"})){
        QuasarAppUtils::Params::log("Error load language : " , QuasarAppUtils::Error);
    }

    QQmlApplicationEngine engine;
    HanoiTowers back(&engine);
    auto root = engine.rootContext();

    if (!QmlNotificationService::init(&engine)) {
        return 1;
    }

    if (!QuasarAppCredits::init(&engine)) {
        return 2;
    }

#ifdef Q_OS_ANDROID
    ActivityHandler *activityHandler = new ActivityHandler(&app);
    engine.rootContext()->setContextProperty(QLatin1String("activityHandler"), activityHandler);
#endif

    root->setContextProperty("backEnd", &back);
    root->setContextProperty("OnlineStatusQml", QVariant::fromValue(OnlineStatusQml{}));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
