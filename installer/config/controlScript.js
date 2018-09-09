function Controller()
{
    installer.uninstallationFinished.connect(this, Controller.prototype.uninstallationFinished);
    installer.installationFinished.connect(this, Controller.prototype.installationFinished);
    runProgramControl();
}


function runProgramControl() {
    if (systemInfo.kernelType === "winnt") {
        Controller.setValue("RunProgram", qsTr("HanoiTowers.exe"));
    }
}

Controller.prototype.uninstallationFinished = function() {

}


Controller.prototype.installationFinished = function() {

}

