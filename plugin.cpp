#include "plugin.h"

Plugin::Plugin()
{
}

Plugin::~Plugin()
{
}

QString Plugin::getNamePlugin()
{
    return "HttpClient";
}

QObject *Plugin::getPluginWidget()
{
    Client *widg = new Client();
    return qobject_cast<QObject *>(widg);
}

QMenu *Plugin::getMenu()
{
}
