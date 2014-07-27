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

#include "headerFiles/dockWidgets/ConsoleInterface.h"
#include "headerFiles/Main.h"

ConsoleInterface::ConsoleInterface()
    : QWidget()
{
    vBoxLayout = new QVBoxLayout();

    output = new QTextEdit();
    input = new QLineEdit();

    vBoxLayout->addWidget(output);
    vBoxLayout->addWidget(input);
    this->setLayout(vBoxLayout);

    connect(input, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));

    print("fast-bit image processing tool  Copyright (C) 2010 - 2011  Jacob Dawid");
    print("This program comes with ABSOLUTELY NO WARRANTY. This is free software,"
          " and you are welcome to redistribute it under certain conditions.");
    print("fast-bit is still in alpha stage. If you encounter any problems,"
          " please feel free to contact us at: jacob.dawid@googlemail.com");
    print(Main::instance().translate("Console", "Ready."));
}

ConsoleInterface::~ConsoleInterface()
{

}

void ConsoleInterface::print(QString message)
{
    output->append(message);
}

void ConsoleInterface::handleUserInput()
{
    emit command(input->text());
    input->setText("");
}
