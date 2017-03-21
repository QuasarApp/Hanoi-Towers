import QtQuick 2.0

Rectangle {
    property var items:[];
    signal click(var obj);
    color: "transparent"
    border.color: "#000000"
    border.width: width*0.05
    radius: 20;
    function push(obj){
        if(items.length>0&&(!obj||obj.mass>items[items.length-1].mass))return false;
        items.push(obj);
        obj.pushofnumber=items.length;
        obj.parent=this;
        obj.flush();
        return true;
    }
    function top(){
       return items[items.length-1];
    }
    function clear(){
        while(items.length){
            items[items.length-1].destroy();
            items.pop();
        }
    }
    function pop(){
        //pushofnumber=value/2;
        items.pop();
    }
    MouseArea{
        onClicked: {
            click(parent);
        }
        anchors.fill: parent;
    }

}
