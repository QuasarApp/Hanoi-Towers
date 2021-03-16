//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Window 2.15

import "./../base" as Base

Item {
    id: row
    property string name: ""
    property int number: 0
    property string points: "0"
    property bool selected: false

    height: source.height

    signal removedRow();
    signal onlineRowChanged(var online);
    signal clicked();

    Rectangle {
        color: (selected)? "#3700f991" : "#0000f991"
        anchors.fill: parent;

        Behavior on color {
            ColorAnimation {
                duration: 500
            }
        }
    }

    Base.Theme{
        id: theme;
    }

    RowLayout {
        id : source

        anchors.left: parent.left
        anchors.right: parent.right

        TextField {
            readOnly: true;
            text: number
            TextMetrics {
                id: textMetrics
                text: "9999"
            }
            Layout.preferredWidth: textMetrics.advanceWidth
        }

        TextField {
            Layout.fillWidth: true
            readOnly: true;
            text: name

            onFocusChanged: {
                if (focus)
                    row.clicked();
            }
        }

        TextField {
            text: points
            readOnly: true;
            Layout.minimumWidth: 5 * Screen.pixelDensity

        }
    }
}


