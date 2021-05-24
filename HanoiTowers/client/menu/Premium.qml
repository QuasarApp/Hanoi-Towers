import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3


Dialog {

    width: parent.width * 0.6
    height: parent.height * 0.8

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    ColumnLayout {
        spacing: 15
        Image {
            id: name
            fillMode: Image.PreserveAspectFit

            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "qrc:/img/premium"

        }

        Label {
            text: qsTr("Tired of ads?")
            font.bold: true
            font.capitalization: Font.AllUppercase
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true

        }

        Label {
            text: qsTr("Especially for you, we have a premium version without ads. Nothing else will stop you from completing the levels!")
            font.bold: false
            font.capitalization: Font.AllUppercase
            wrapMode: Text.WordWrap
            Layout.fillWidth: true


        }

        Button {
            text: qsTr("Get Premium Hanoi towers")
            Layout.alignment: Layout.Center

            onClicked: {
                Qt.openUrlExternally("https://play.google.com/store/apps/details?id=df.mobily.premium_hanoi_towers");
            }

        }
        anchors.fill: parent
    }
    standardButtons: Dialog.Ok


}
