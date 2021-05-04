//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Dialog {

    id: helpDialog

    height: parent.height * 0.9
    width: parent.width * 0.9
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2


    ColumnLayout {

        spacing: 40

        Image {
            id: example

            fillMode: Image.PreserveAspectFit

            Layout.preferredHeight:  helpDialog.height * 0.5
            Layout.fillWidth: true;

            source: "/img/Help"
        }

        Label {
            id: textContainer

            Layout.fillHeight: true;
            Layout.fillWidth: true;

            wrapMode:Text.Wrap ;

            text: qsTr("Your task is to transfer discs of different sizes" +
 "from the left tower to third tower." +
 "You can only transfer the top drive of the tower." +
 "You can not transfer several disks at once and put larger disks on small disks.");

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        CheckBox {
            id: indicator

            Layout.alignment: Qt.AlignBottom
            text: qsTr("Do not show again")
            Component.onCompleted: {
                if (backEnd) {
                    checked = !backEnd.isFirst()
                }
            }

            onCheckedChanged: {
                backEnd.setShowHelp(!indicator.checked);
            }

        }

        anchors.fill: parent
    }

    standardButtons: Dialog.Ok


}
