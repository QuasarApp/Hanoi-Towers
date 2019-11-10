import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13

Item {
    GridLayout {
        id: gridLayout
        rows: 2
        columns: 3
        anchors.fill: parent


        Switch {
            id: element
            text: qsTr("Online user")
        }


        TextField {
            Layout.fillWidth: true

            id: textField
            text: qsTr("Enter the name of new user")
        }

        Button {
            id: button
            text: qsTr("Create new user")
        }

        ListView {

            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 3

            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }

    }

}
