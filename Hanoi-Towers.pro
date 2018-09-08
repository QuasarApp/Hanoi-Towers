TEMPLATE = subdirs
CONFIG += ordered

include($$PWD/installer/deploy/deployFiles.pri)
message( DEPLOY_FILES_MASTER = $$DEPLOY_FILES)

ENABLE_SNAP = 1 #only linux
ENABLE_INSTALLER = 1 #only desctop

SUBDIRS += hanoi_towers \
        CQtDeployer

equals( ENABLE_INSTALLER, 1) {
    !android:{
        message(desktopVersion: enabled)
        CONFIG(release, debug|release): {

            SUBDIRS += installer

        } else {
            message( Selected Debug mode. The installer will not be created )

        }
    }
}

equals( ENABLE_SNAP, 1) {
    !android:{
        message(desktopVersion: enabled)
        CONFIG(release, debug|release): {

            SUBDIRS += installer/packages/HanoiTowers/snap.pro

        } else {
            message( Selected Debug mode. The snap will not be created )

        }
    }
}
