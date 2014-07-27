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

#include "PluginManager.h"
#include <QLibrary>
#include <string>
#include <QPluginLoader>

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

QString PluginManager::errorString()
{
    return m_errorString;
}

bool PluginManager::loadPlugin(QString fileName)
{
    if(fileName.length())
    {
        QPluginLoader pluginLoader(fileName);
        QObject* pluginObject = pluginLoader.instance();
        PluginProxy pluginProxy(qobject_cast<PluginInterface*>(pluginObject));

        if(pluginProxy.isValid())
        {
            bool alreadyLoaded = false;
            foreach(PluginProxy loadedPlugin, m_plugins)
                if(loadedPlugin.identifier() == pluginProxy.identifier())
                    alreadyLoaded = true;

            if(!alreadyLoaded)
                m_plugins.append(pluginProxy);

            emit configurationChanged();
            return true;
        }

        m_errorString = pluginLoader.errorString();
        return false;
    }
    m_errorString = "File was not found.";
    return false;
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
