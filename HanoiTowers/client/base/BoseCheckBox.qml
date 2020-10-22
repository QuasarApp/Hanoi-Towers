//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.9
import QtQuick.Controls 2.2

CheckBox {
    Theme{
        id: theme;
    }
    contentItem: Text {
        text: parent.text
        font.pixelSize: parent.height * 0.8
        opacity: enabled ? 1.0 : 0.3
        color: parent.down ? theme.buttonsTextColor : theme.buttonsTextColorPresed
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    indicator.height: height
    indicator.width: height

    width: theme.buttonsWidth
    height: theme.buttonsHeight
}
