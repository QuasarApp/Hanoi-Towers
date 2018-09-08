import QtQuick 2.9
import QtQuick.Controls 2.2
import "./base" as Base

Dialog {
    standardButtons: DialogButtonBox.Ok

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    property alias text : textContainer.text

    Base.BaseText {
        id: textContainer

        anchors.fill: parent

        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignTop
    }
}
