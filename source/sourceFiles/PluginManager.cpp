#include "headerFiles/PluginManager.h"
#include <QLibrary>
#include <string>

using namespace std;
PluginManager PluginManager::singleton;

PluginManager::PluginManager()
    : QObject()
{

}

PluginManager::~PluginManager()
{

}

PluginManager& PluginManager::instance()
{
    return PluginManager::singleton;
}

void PluginManager::loadPlugin(QString fileName)
{
    if(fileName.length())
    {
        QLibrary library(fileName);
        typedef Plugin* (*ExportPluginFunction)();
        ExportPluginFunction exportPlugin = (ExportPluginFunction) library.resolve("exportPlugin");
        if(exportPlugin)
        {
            qDebug("Plugin is valid, querying for content.");
            Plugin* plugin = exportPlugin();
            if(plugin)
            {
                qDebug("Library identifies with \"%s\"", plugin->identifier().toStdString().c_str());
            }
        }
        else
        {
            qDebug("Plugin is not valid.");
            // This is no a valid plugin.
        }
    }

    emit configurationChanged();
}
