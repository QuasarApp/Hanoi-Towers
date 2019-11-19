//#
//# Copyright (C) 2018 - 2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import "./../base" as Base

Item {
    property string title: qsTr("");
    property string color:
    Image {

    }

    Base.BaseButton{
        id: ret;

        text: qsTr("Main menu");
    }

}
