import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    id: tover
    property var items: []
    signal click(var obj)

    Rectangle {

        id: centerLine
        height: parent.height
        width: parent.width / 20
        x: parent.width / 2 - width / 2
        y: 0
//        color: "#ff0000"
        radius: 20
//        gradient: Gradient {
//            GradientStop {
//                position: 0.00;
//                color: "#f0cb98";
//            }
//            GradientStop {
//                position: 1.00;
//                color: "#d9b077";
//            }
//        }

        LinearGradient {
            source: parent
            anchors.fill: parent
            start: Qt.point(0, centerLine.height / 2)
            end: Qt.point(centerLine.width, parent.height / 2)
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

//        anchors.top: tover.top
//        anchors.topMargin: 60
//        anchors.bottomMargin: 0
//        anchors.bottom: tover.bottom

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
