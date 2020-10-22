//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import "./../base" as Base

Item {
    id: row
    property string name: ""
    property bool online: false
    property string record: "0"
    property int recordLength: 0
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

    RowLayout {
        id : source

        anchors.left: parent.left
        anchors.right: parent.right

        Base.Theme{
            id: theme;
        }

        Switch {
            text: qsTr("Online user")
            position: online
            onPositionChanged: {
                onlineRowChanged(Boolean(position));
            }

            ToolTip.visible: pressed || hovered
            ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
            ToolTip.timeout: 10000
            ToolTip.text: qsTr("If this option is enabled, your saves and the record will be saved on the network.")

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

        Text {
            text: record
            Layout.minimumWidth: recordLength - deleteUser.width

        }

        Base.BaseButton {
            id: deleteUser;
            text: "X"

            Layout.maximumHeight:  theme.smallbuttonsSize
            Layout.maximumWidth: theme.smallbuttonsSize

            onClicked: {
                removedRow();
            }
        }
    }
}


