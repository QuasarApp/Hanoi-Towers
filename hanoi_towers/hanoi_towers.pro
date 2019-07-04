TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    backEnd.cpp

RESOURCES += qml.qrc
TARGET = hanoi-towers

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET=HanoiTowers

QT_DIR = $$[QT_HOST_BINS]
LUPDATE = $$QT_DIR/lupdate
LRELEASE = $$QT_DIR/lrelease

CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release

} else {
    DESTDIR = $$PWD/build/debug
}


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    import.qml \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    languages/ru.ts \
    languages/ja.ts \
    languages/tr.ts \
    languages/en.ts \
    languages/ua.ts
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    backEnd.h

TRANSLATIONS += \
    languages/ru.ts \
    languages/ja.ts \
    languages/tr.ts \
    languages/en.ts \
    languages/ua.ts

commands += "$$LUPDATE $$PWD/hanoi_towers.pro"
commands += "$$LRELEASE $$PWD/hanoi_towers.pro"

for(command, commands) {
    system($$command)|error("Failed to run: $$command")
}

RC_ICONS = res/icon.ico
