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

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "PluginProxy.h"
#include <QString>
#include <QObject>

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager& instance();

    bool loadPlugin(QString fileName);
    QList<QString> availablePlugins();
    QList<QString> availableFunctions(QString plugin);

    QString errorString();
signals:
    void configurationChanged();

private:
    PluginManager();
    ~PluginManager();

    QString m_errorString;
    QList<PluginProxy> m_plugins;
    static PluginManager singleton;
};

#endif // PLUGIN_MANAGER_H
