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

#include "headerFiles/Main.h"
#include "headerFiles/dockWidgets/Console.h"

Console::Console(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(Main::instance().translate("Console", "Console"));
    setObjectName("console");
    construct();

    connect(&Main::instance(), SIGNAL(languageChanged()), this, SLOT(changeLanguage()));
    connect(centralWidget, SIGNAL(command(QString)), this, SLOT(handleCommand(QString)));
    changeLanguage();
}

Console::~Console()
{
}

void Console::print(QString message)
{
    centralWidget->print(message);
}

void Console::changeLanguage()
{
    setWindowTitle(Main::instance().translate("Console", "Console"));
}

void Console::handleCommand(QString _command)
{
    emit command(_command);
}

void Console::construct()
{
    centralWidget = new ConsoleInterface();
    setWidget(centralWidget);
}
