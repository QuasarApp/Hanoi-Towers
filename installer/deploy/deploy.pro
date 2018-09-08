TEMPLATE = aux

INSTALLER = deployApp

INPUT = DEPLOY_FILES
deployApp.input = INPUT
deployApp.output = $$INSTALLER


QT_DIR = $$dirname(QMAKE_QMAKE)
QML_DIR = $$QT_DIR/../qml


WINDEPLY = $$QT_DIR/windeployqt.exe
MACDEPLY = $$QT_DIR/macdeployqt
LINUXDEPLOY = $$PWD/linuxdeployqt-continuous-x86_64.AppImage

message( QML_DIR = $$QML_DIR)
message( WINDEPLY = $$WINDEPLY)
message( MACDEPLY = $$MACDEPLY)
message( LINUXDEPLOY = $$LINUXDEPLOY)

win32 {
    deployApp.commands += "$$WINDEPLY --qmldir $$QML_DIR $$DEPLOY_FILES"
}

unix {
    deployApp.commands += "$$LINUXDEPLOY --qmldir=$$QML_DIR --qmake=$$QMAKE_QMAKE $$DEPLOY_FILES"
}

mac {
    deployApp.commands += "$$MACDEPLY --qmldir $$QML_DIR $$DEPLOY_FILES"
}
    message( deployComand = "$$deployApp.commands")

commands += "chmod +x $$LINUXDEPLOY"

for(command, commands) {
    system($$command)|error("Failed to run: $$command")
}

