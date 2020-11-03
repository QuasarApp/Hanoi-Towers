//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


function dp(pixelDensity, x) {
	return (pixelDensity * 25.4 < 120) ? x : x*(pixelDensity * 25.4/160);
}

function baseColor() {
    return "#303030"
}

function primaryColor() {
    return "#acacac"
}

function textColor() {
    return "#a6aaa2"
}

function textAltColor() {
    return "#434f4d"
}

function backgroundColor() {
    return "#eeeeee"
}

function backgroundAltColor() {
    return "#aaaaaa"
}

function baseFontSize(pixelDensity){
    return Number(dp(pixelDensity, 14));
}

function baseGameStateFontSize(pixelDensity){
    return Number(dp(pixelDensity, 16));
}

function headerFontSize(pixelDensity){
    return Number(dp(pixelDensity, 28));
}

