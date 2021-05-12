//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    id: tover
    property var items: []
    property var itemsMassArray: []
    property int number: 0

    signal click(var obj)

    Rectangle {
        color: "#d1cccc"
        anchors.bottomMargin: 0
        anchors.bottom: parent.bottom
        height: 10
        x: 0
        width: parent.width
    }

    function up() {
        if (items.length <= 0 )
            return null

        const obj = top();
        pop();

        obj.x = (tover.width / 2) - (obj.width / 2)
        obj.y = 0 - obj.height;

        return obj

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
