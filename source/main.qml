import QtQuick 2.5
import QtQuick.Controls 1.4
ApplicationWindow {
    visible: true
    id: gameWindow;
    width: 640
    height: 480
    title: qsTr("Hanoi Towers")
    Loader{
        id:core;
        source: "game.qml";
        anchors.fill: parent;
        onLoaded: {
            item.start(3);
        }
    }
}
