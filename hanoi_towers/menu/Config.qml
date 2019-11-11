import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import "./../base" as Base

Item {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    Rectangle {
        id: head
        color: theme.headerColor
        height: parent.height * 0.15;
        RowLayout {

            Base.BaseText {
                Layout.alignment: Qt.AlignCenter

                text: qsTr("Settings");
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: theme.headerSize;
            }

            Base.BaseButton {
                text: qsTr("Return to main menu");
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: theme.pading

                onClicked: {
                    menuPage.parent.source = "MainMenu.qml"
                }
            }

            anchors.fill: parent
        }
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

    }

    Row {

        Image {
            id: colorsView
            fillMode: Image.PreserveAspectFit
            source: (backEnd.randomColor)? "../img/random":"../img/standart"
            height: width
            width: menuPage.width * 0.5

        }

        Column {

            id: colors
            width: colorsView.width
            height: colorsView.height
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.1
            anchors.left: colorsView.right


            RadioButton {
                id: r1
                checked: !backEnd.randomColor
                text: qsTr("Standart color")

                width: colorsView.width;
                onCheckedChanged: {
                    backEnd.randomColor = false;
                }
            }

            RadioButton {
                id:r2
                checked: backEnd.randomColor
                text: qsTr("Random color")
                width: colorsView.width;
                onCheckedChanged: {
                    backEnd.randomColor = true;
                }
            }

            CheckBox {
                height: colorsView.height * 0.3;
                width: colorsView.width;
                text: qsTr("Animation")
                checked: backEnd.animation
                onCheckedChanged: {
                    backEnd.animation = checked;
                }
            }

            Layout.alignment: Qt.AlignLeft
        }

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: head.bottom

    }

}

