import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import "./../base" as Base
import BackEnd 1.0

Page {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    BackEnd {
        id: backEnd
    }

    header: Rectangle {
        color: "#800af587"
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

    }

    contentItem: Item {
        id: content;
        RowLayout {

            Image {
                id: colorsView
                fillMode: Image.PreserveAspectFit
                source: (backEnd.randomColor)? "../img/random":"../img/standart"
                width: (content.width * 0.3 > height)? height: content.width * 0.3
                height: content.height
            }

            ColumnLayout {

                id: colors
                width: parent.width * 0.5

                RadioButton {
                    id: r1
                    checked: !backEnd.randomColor
                    text: qsTr("Standart color")

                    onCheckedChanged: {
                        backEnd.randomColor = false;
                    }
                }

                RadioButton {
                    id:r2
                    checked: backEnd.randomColor
                    text: qsTr("Random color")

                    onCheckedChanged: {
                        backEnd.randomColor = true;
                    }
                }

                CheckBox{

                    text: qsTr("Animation")
                    checked: backEnd.animation
                    onCheckedChanged: {
                        backEnd.animation = checked;
                    }
                }

                Layout.alignment: Qt.AlignLeft
            }
            anchors.fill: parent
        }
    }
}

