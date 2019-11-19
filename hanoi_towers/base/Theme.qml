//#
//# Copyright (C) 2018 - 2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.9
import QtQuick.Window 2.1
import "utils.js" as Utils

Item {
    readonly property int fontSize: Utils.baseFontSize(Screen.pixelDensity)
    readonly property int headerSize: Utils.headerFontSize(Screen.pixelDensity);
    readonly property int buttonsWidth: Utils.dp(Screen.pixelDensity, 80)
    readonly property int buttonsHeight: Utils.dp(Screen.pixelDensity, 40)

    readonly property int smallbuttonsSize: Utils.dp(Screen.pixelDensity, 40)

    readonly property int popUpWidth: Utils.dp(Screen.pixelDensity, 150)
    readonly property int popUpHeight: Utils.dp(Screen.pixelDensity, 80)
    readonly property string buttonsTextColor: Utils.textColor()
    readonly property string buttonsTextColorPresed: Utils.textAltColor()
    readonly property string baseColor: Utils.baseColor()
    readonly property string atlColor: Utils.primaryColor()
    readonly property string backgroundColor: Utils.backgroundColor()
    readonly property string backgroundAltColor: Utils.backgroundAltColor()
    readonly property int pading: Utils.dp(Screen.pixelDensity, 10);
    readonly property string headerColor: "#800af587"


}
