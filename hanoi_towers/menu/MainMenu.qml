import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./../base" as Base

Page {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    header: Rectangle {
        color: "#800af587"
        height: parent.height * 0.15;
        RowLayout {

            Base.BaseText {
                Layout.alignment: Qt.AlignCenter

                text: qsTr("Hanoi Towers");
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: theme.headerSize;
            }
            anchors.fill: parent
        }

    }

    contentItem: Item {
        id: content;


        ColumnLayout {

            Base.BaseButton {
                id: load;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.18
                Layout.alignment: Qt.AlignCenter

                text: qsTr("continue");
                width:  about.width * 0.8;
                onClicked: {
                    menuPage.parent.load()

                }
            }

            Base.BaseButton {
                id: start;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.18
                Layout.alignment: Qt.AlignCenter

                text: qsTr("start");
                width:  about.width * 0.8;
                onClicked: {
                    menuPage.parent.start()

                }
            }

            Base.BaseButton {
                id: about;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.18
                Layout.alignment: Qt.AlignCenter
                text: qsTr("About");
                width:  config.width * 0.8;
                onClicked: {
                    menuPage.parent.source = "../about.qml"

                }
            }

            Base.BaseButton {
                id: config;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.18
                Layout.alignment: Qt.AlignCenter
                text: qsTr("Config");
                width:  exit.width * 0.8;
                onClicked: {
                    menuPage.parent.source = "Config.qml"
                }
            }

            Base.BaseButton {
                id: exit;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.18
                Layout.alignment: Qt.AlignCenter
                width: content.width * 0.5;
                text: qsTr("exit");
                onClicked: {
                    Qt.quit();
                }
            }
            anchors.fill: parent
        }
    }


}

