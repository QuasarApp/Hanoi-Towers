//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QuasarAppCreditsModule 1.0


Credits {
    state: "about"
    developersList: [
        {
            section: qsTr("## QuasarApp Core team:"),
            sectionList: [
                "* Yankovich Andrei " + qsTr("(Programmer)"),
                "* Chernenkov Oleg " + qsTr("(Designer)"),
            ]
        }
    ]
}
