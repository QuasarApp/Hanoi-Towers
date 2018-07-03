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

                RowLayout{

                    Base.BaseText{
                        text: qsTr("Move animation:");
                    }

                    StatusIndicator {
                        anchors.centerIn: parent
                        active: backEnd.animation;
                        color: "#800af587"

                        MouseArea {
                            anchors.fill:  parent
                            onClicked:{
                                backEnd.animation = !parent.active;
                            }
                        }
                    }
                    Layout.alignment: Qt.AlignCenter
                }
                Layout.alignment: Qt.AlignLeft
            }
            anchors.fill: parent
        }
    }
}

