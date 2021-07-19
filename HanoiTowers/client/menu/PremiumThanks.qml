import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3



Dialog {

    width: parent.width * 0.6
    height: parent.height * 0.8

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2


    ColumnLayout {
        spacing: 5
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

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Image {
                id: premUserImg
                fillMode: Image.PreserveAspectFit

                source: "qrc:/img/res/galochka.png"
                sourceSize.width: 80
                sourceSize.height: 80

            }

            Label {
                text: qsTr("You are now our premium user and we won't dare bother you with ads anymore.")
                font.bold: false
                font.capitalization: Font.AllUppercase
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Image {
                id: unlockImg
                fillMode: Image.PreserveAspectFit

                source: "qrc:/img/res/unlock.png"
                sourceSize.width: 80
                sourceSize.height: 80

            }


            Label {
                text: qsTr("Now levels from 1 to 15 are available to you. Enjoy your game!")
                font.bold: false
                font.capitalization: Font.AllUppercase
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
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
