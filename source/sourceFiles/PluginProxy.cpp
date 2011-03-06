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

#include "headerFiles/PluginProxy.h"

PluginProxy::PluginProxy(Plugin* plugin)
    : m_plugin(plugin),
      m_valid(false)
{
    if(plugin)
    {
        QList<QString> content = plugin->content();
        foreach(QString function, content)
        {
            // TODO: Build bridge to function.
        }
        m_valid = true;
    }
}

QList<QString> PluginProxy::functions()
{
    return m_plugin->content();
}
