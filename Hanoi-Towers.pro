TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += hanoi_towers

include($$PWD/installer/installerHanoiTower.pri)

QMAKE_EXTRA_TARGETS += \
    test
