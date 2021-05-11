/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "activityhandler.h"

#ifdef Q_OS_ANDROID

#include <QAndroidIntent>

const int REQUEST_CODE = 123;
const jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");

ActivityHandler *ActivityHandler::m_instance = nullptr;

ActivityHandler::ActivityHandler(QObject *parent) : QObject(parent) {
    m_instance = this;
}

void ActivityHandler::showSecondActivity() {
    QAndroidIntent activityIntent(QtAndroid::androidActivity().object(),
                                  "org/qtproject/example/activityhandler/CustomActivity");

    QtAndroid::startActivity(
            activityIntent.handle(), REQUEST_CODE,
            [this](int requestCode, int resultCode, const QAndroidJniObject &data) {
                activityReceiver(requestCode, resultCode, data);
            });
}

void ActivityHandler::activityReceiver(int requestCode,
                                       int resultCode,
                                       const QAndroidJniObject &data) {
    if (requestCode == REQUEST_CODE) {
        if (resultCode == RESULT_OK) {
            const QAndroidJniObject key = QAndroidJniObject::fromString("message");
            const QAndroidJniObject message = data.callObjectMethod(
                    "getStringExtra", "(Ljava/lang/String;)Ljava/lang/String;", key.object());
            if (message.isValid())
                emit ActivityHandler::instance()->receiveFromActivityResult(message.toString());
        } else {
            emit ActivityHandler::instance()->receiveFromActivityResult("Rejected!");
        }
    }
}
#endif
