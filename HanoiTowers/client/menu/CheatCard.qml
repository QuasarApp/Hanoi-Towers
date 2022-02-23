import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.1
import QtQuick.Controls.Material 2.15

Dialog {

    width: parent.width * 0.6
    height: parent.height * 0.8

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Try our new application!")
            font.bold: true
            font.capitalization: Font.AllUppercase
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true

        }

        Image {
            fillMode: Image.PreserveAspectFit

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.preferredWidth: parent.width * 0.95
            Layout.preferredHeight: width * 0.4

            source: "qrc:/img/res/CheatCard_Banner.jpg"
        }


        Label {
            text: qsTr("Cheat Card is Free mobile application for create bonus cards for your business")
            font.bold: false
            font.capitalization: Font.AllUppercase
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            wrapMode: Label.WordWrap

        }

        Button {
            text: qsTr("Get CheatCard")
            Layout.alignment: Layout.Center
            Material.background: Material.LightGreen

            onClicked: {
                Qt.openUrlExternally("https://play.google.com/store/apps/details?id=quasarapp.core.cheatcard");
            }
        }
    }

    standardButtons: Dialog.Ok
}
