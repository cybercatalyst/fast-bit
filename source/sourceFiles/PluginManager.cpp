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
            qDebug("Plugin is valid, querying for content.");
            Plugin* plugin = exportPlugin();
            if(plugin)
            {
                qDebug("Library identifies with \"%s\"", plugin->identifier().toStdString().c_str());
                QList<QString> content = plugin->content();
                foreach(QString function, content)
                {
                    qDebug("Found function \"%s\"", function.toStdString().c_str());
                }
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
