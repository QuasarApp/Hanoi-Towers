function Controller()
{
    installer.uninstallationFinished.connect(this, Controller.prototype.uninstallationFinished);
    installer.installationFinished.connect(this, Controller.prototype.installationFinished);
    runProgramControl();
}


function runProgramControl() {
    if (systemInfo.kernelType === "winnt") {
        installer.setValue("RunProgram", "@TargetDir@/HanoiTowers.exe");
    } else {
        installer.setValue("RunProgram", "@TargetDir@/HanoiTowers.sh");
    }
}

Controller.prototype.uninstallationFinished = function() {

}


Controller.prototype.installationFinished = function() {

}

