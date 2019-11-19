#
# Copyright (C) 2018 - 2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += NetworkProtocol \
           SimpleQmlNotify \
           hanoi_towers

NetworkProtocol.file = $$PWD/QtNetworkProtocol/NetworkProtocol.pro
SimpleQmlNotify.file = $$PWD/SimpleQmlNotify/QmlNotify.pro

include($$PWD/installer/installerHanoiTower.pri)

QMAKE_EXTRA_TARGETS += \
    test
