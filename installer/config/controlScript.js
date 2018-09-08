function Controller()
{
    installer.uninstallationFinished.connect(this, Controller.prototype.uninstallationFinished);
    installer.installationFinished.connect(this, Controller.prototype.installationFinished);
}


Controller.prototype.uninstallationFinished = function()
{

}


Controller.prototype.installationFinished = function()
{

}

