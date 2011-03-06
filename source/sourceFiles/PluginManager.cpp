/* fast-bit image processing tool
 * Copyright (C) 2010 - 2011 Jacob Dawid
 * jacob.dawid@googlemail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
            qDebug("Plugin seems to be valid, querying for content.");
            PluginProxy pluginProxy(exportPlugin());

            if(pluginProxy.isValid())
            {
                bool alreadyLoaded = false;
                foreach(PluginProxy loadedPlugin, m_plugins)
                    if(loadedPlugin.identifier() == pluginProxy.identifier())
                        alreadyLoaded = true;

                if(!alreadyLoaded)
                    m_plugins.append(pluginProxy);
            }
        }
        else
        {
            qDebug("Plugin is not valid.");
            // This is not a valid plugin.
        }
    }

    emit configurationChanged();
}

QList<QString> PluginManager::availablePlugins()
{
    QList<QString> pluginList;
    foreach(PluginProxy proxy, m_plugins)
        pluginList.append(proxy.identifier());
    return pluginList;
}

QList<QString> PluginManager::availableFunctions(QString plugin)
{
    foreach(PluginProxy proxy, m_plugins)
        if(proxy.identifier() == plugin)
            return proxy.functions();
    return QList<QString>();
}
