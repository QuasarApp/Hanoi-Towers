TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += NetworkProtocol \
           hanoi_towers

NetworkProtocol.file = $$PWD/QtNetworkProtocol/NetworkProtocol.pro

include($$PWD/installer/installerHanoiTower.pri)

QMAKE_EXTRA_TARGETS += \
    test
