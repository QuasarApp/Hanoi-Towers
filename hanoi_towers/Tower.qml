import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    id: tover
    property var items: []
    property var itemsMassArray: []
    property int number: 0

    property var upPlate: null
    signal click(var obj)

    Rectangle {

        id: centerLine
        height: parent.height
        width: parent.width / 20
        x: parent.width / 2 - width / 2
        y: 0
        radius: 20


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

    function up() {
        if (items.length <= 0 )
            return null

        const obj = top();
        pop();

        obj.x = (tover.width / 2) - (obj.width / 2)
        obj.y = 0 - obj.height;

        upPlate = obj;
        return upPlate

    }

    function push(obj) {
        if (items.length > 0 && (!obj
                                 || obj.mass > items[items.length - 1].mass))
            return false

        items.push(obj)
        itemsMassArray.push(obj.mass)

        obj.pushofnumber = items.length

        obj.parent = this

        const temp = obj.durationAnimation;
        obj.durationAnimation = 0;

        obj.x = (tover.width / 2) - (obj.width / 2)
        obj.y = 0 - obj.height;
        obj.durationAnimation = temp;


        return true
    }

    function top() {
        itemsMassArray.pop()
        return items[items.length - 1]
    }

    function clear() {
        while (items.length) {
            items[items.length - 1].destroy()
            items.pop()
            itemsMassArray.pop()

        }
    }

    function pop() {
        items.pop()
    }

    function init(array) {

    }

    MouseArea {
        onClicked: {
            click(parent)
        }
        anchors.fill: parent
    }
}
