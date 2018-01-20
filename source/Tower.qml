import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: tover
    property var items: []
    signal click(var obj)
    color: "transparent"

    Rectangle {

        id: centerLine
        width: parent.width / 20
        x: parent.width / 2 - width / 2
        radius: 20

        LinearGradient {
            source: parent
            anchors.fill: parent
            start: Qt.point(0, parent.height / 2)
            end: Qt.point(parent.width, parent.height / 2)
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#f0cb98"
                }
                GradientStop {
                    position: 1.0
                    color: "#d9b077"
                }
            }
        }

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottomMargin: 0
        anchors.bottom: parent.bottom
    }

    Image {

        id: bottomLine
        width: parent.width
        height: 10
        x: 0
        fillMode: Image.TileVertically
        source: "/textures/res/wood.png"

        anchors.bottomMargin: 0
        anchors.bottom: parent.bottom
    }

    radius: 20
    function push(obj) {
        if (items.length > 0 && (!obj
                                 || obj.mass > items[items.length - 1].mass))
            return false
        items.push(obj)
        obj.pushofnumber = items.length
        obj.parent = this
        return true
    }

    function top() {
        return items[items.length - 1]
    }

    function clear() {
        while (items.length) {
            items[items.length - 1].destroy()
            items.pop()
        }
    }
    function pop() {
        items.pop()
    }

    MouseArea {
        onClicked: {
            click(parent)
        }
        anchors.fill: parent
    }
}
