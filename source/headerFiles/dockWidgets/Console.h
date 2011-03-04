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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDockWidget>
#include <QTextEdit>

class Console : public QDockWidget
{
    Q_OBJECT

public:
    Console(QWidget *parent = 0);
    ~Console();

public slots:
    /**
      * Prints a message in the console.
      */
    void print(QString message);

    /**
      * Changes the language.
      */
    void changeLanguage();

private:
    /**
      * Construct console window.
      */
    void construct();

    /**
      * Central widget.
      */
    QTextEdit *centralWidget;
};

#endif // CONSOLE_H
