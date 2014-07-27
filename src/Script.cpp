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

#include "Main.h"
#include "Script.h"

Script::Script(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(Main::instance().translate("Script", "Script"));
    setObjectName("script");
    construct();

    connect(&Main::instance(), SIGNAL(languageChanged()), this, SLOT(changeLanguage()));
    m.scriptingInterface->restoreState(Main::instance().settings()->value("scriptingWindowState").toByteArray());
}

Script::~Script()
{
}

void Script::changeLanguage()
{
    setWindowTitle(Main::instance().translate("Script", "Script"));
}

ScriptingInterface *Script::scriptingInterface()
{
    return m.scriptingInterface;
}

void Script::construct()
{
    m.scriptingInterface = new ScriptingInterface(this);
    setWidget(m.scriptingInterface);
}

void Script::saveWindowState()
{
    Main::instance().settings()->setValue("scriptingWindowState", m.scriptingInterface->saveState());
}
