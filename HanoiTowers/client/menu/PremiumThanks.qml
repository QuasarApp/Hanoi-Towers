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
            text: qsTr("Thanks for your support!")
            font.bold: true
            font.capitalization: Font.AllUppercase
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true

        }

        Label {
            text: qsTr("You are now our premium user and we won't dare bother you with ads anymore.")
            font.bold: false
            font.capitalization: Font.AllUppercase
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        CheckBox {
            id: doNotShowAgain
            text: qsTr("Do not show again ")
            Layout.alignment: Layout.Center

        }
        anchors.fill: parent
    }

    standardButtons: Dialog.Ok

    onClosed: {
        backEnd.showCredits = !doNotShowAgain.checked;
    }
}
