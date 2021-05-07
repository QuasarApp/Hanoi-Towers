/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#ifndef ACTIVITYHANDLER_H
#define ACTIVITYHANDLER_H

#ifndef Q_OS_ANDROID
#include <QObject>
#include <QtAndroid>

class ActivityHandler : public QObject
{
    Q_OBJECT

public:
    ActivityHandler(QObject *parent = nullptr);
    static ActivityHandler *instance() { return m_instance; }

    Q_INVOKABLE void showSecondActivity();
    void activityReceiver(int requestCode, int resultCode, const QAndroidJniObject &data);

signals:
    void receiveFromActivityResult(const QString &message);

private:
    static ActivityHandler *m_instance;
};

#endif

#endif // ACTIVITYHANDLER_H
