import QtQuick 2.9
import QtQuick.Controls 2.2
Button{
    Theme{
        id: theme;
    }
    id: ok
    text: qsTr("ok")
    contentItem: Text {
        text: parent.text
        font.pixelSize: theme.fontSize
        opacity: enabled ? 1.0 : 0.3
        color: parent.down ? theme.buttonsTextColor : theme.buttonsTextColorPresed
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    width: theme.buttonsWidth
    height: theme.buttonsHeight

}
