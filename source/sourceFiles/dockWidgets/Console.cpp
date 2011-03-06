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
    changeLanguage();
}

Console::~Console()
{
}

void Console::print(QString message)
{
    centralWidget->append(message);
}

void Console::changeLanguage()
{
    setWindowTitle(Main::instance().translate("Console", "Console"));
}

void Console::construct()
{
    centralWidget=new QTextEdit();
    centralWidget->setReadOnly(true);
    setWidget(centralWidget);
    print("fast-bit image processing tool  Copyright (C) 2010 - 2011  Jacob Dawid");
    print("This program comes with ABSOLUTELY NO WARRANTY. This is free software,"
          " and you are welcome to redistribute it under certain conditions.");
    print("fast-bit is still in alpha stage. If you encounter any problems,"
          " please feel free to contact us at: jacob.dawid@googlemail.com");
    print(Main::instance().translate("Console", "Ready."));
}
