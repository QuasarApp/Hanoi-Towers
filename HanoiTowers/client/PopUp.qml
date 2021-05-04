//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.9
import QtQuick.Controls 2.2

Dialog {
    standardButtons: DialogButtonBox.Ok

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    property alias text : textContainer.text
    property var action: function () {}

    Label {
        id: textContainer

        anchors.fill: parent

        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignTop
    }

    onAccepted: {
        action();
    }
}
