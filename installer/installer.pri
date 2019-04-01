QT_DIR = $$dirname(QMAKE_QMAKE)
QML_DIR = $$PWD/../hanoi_towers/
DEPLOY_TARGET = $$PWD/../hanoi_towers/build/release

LUPDATE = $$QT_DIR/lupdate
LRELEASE = $$QT_DIR/lrelease

win32:DEPLOYER = $$PWD/../CQtDeployerBinaries/Windows/cqtdeployer.exe
unix:DEPLOYER = cqtdeployer

OUT_FILE = installer

CONFIG(serverbuild): {
    EXEC = binarycreator
} else: {

    BINARY_LIST
    exists( $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/ ) {
          message( "QtInstallerFramework v3.0: yes" )
          BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/binarycreator
    }
    exists( $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/ ) {
          message( "QtInstallerFramework v2.0: yes" )
          BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/binarycreator
    }

    isEmpty (BINARY_LIST) {
          error( "QtInstallerFramework not found!" )
    }

    EXEC=$$first(BINARY_LIST)
    message( selected $$EXEC  )

}

win32 {
    LUPDATE = $${LUPDATE}.exe
    LRELEASE = $${LRELEASE}.exe
    EXEC = $${EXEC}.exe
    OUT_FILE = $${OUT_FILE}.exe
}

SUPPORT_LANGS = ru

defineReplace(findFiles) {
    patern = $$1
    path = $$2

    all_files = $$files(*$${patern}, true)
    win32:all_files ~= s|\\\\|/|g
    win32:path ~= s|\\\\|/|g

    for(file, all_files) {
        result += $$find(file, $$path)
    }

    return($$result)
}

XML_FILES = $$files(*.xml, true)

for(LANG, SUPPORT_LANGS) {
    for(XML, XML_FILES) {
        FILE_PATH = $$dirname(XML)

        JS_FILES = $$findFiles(".js", $$FILE_PATH)
        UI_FILES = $$findFiles(".ui", $$FILE_PATH)

        commands += "$$LUPDATE $$JS_FILES $$UI_FILES -ts $$FILE_PATH/$${LANG}.ts"
        TS_FILES += $$FILE_PATH/$${LANG}.ts

    }

    for(TS, TS_FILES) {
        commands += "$$LRELEASE $$TS"
    }
}

for(command, commands) {
    system($$command)|error("Failed to run: $$command")
}

BASE_DEPLOY_FLAGS = clear -qmake $$QMAKE_QMAKE -targetDir $$PWD/packages/HanoiTowers/data

deploy_depends.commands += $$DEPLOYER -bin $$DEPLOY_TARGET -qmlDir $$QML_DIR $$BASE_DEPLOY_FLAGS

create_installer.commands = $$EXEC \
                               -c $$PWD/config/config.xml \
                               -p $$PWD/packages \
                               $$PWD/$$OUT_FILE

OTHER_FILES += \
    $$PWD/config/controlScript.js \
    $$PWD/config/config.xml \
    $$PWD/packages/HanoiTowers/meta/package.xml \
    $$PWD/packages/HanoiTowers/meta/installscript.js \
    $$PWD/packages/HanoiTowers/meta/ru.ts \
    $$PWD/packages/installer/meta/package.xml \
    $$PWD/packages/installer/meta/installscript.js \
    $$PWD/packages/installer/meta/ru.ts

create_installer.depends = deploy_depends

QMAKE_EXTRA_TARGETS += \
    deploy_depends \
    create_installer
