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

#ifndef SCRIPT_H
#define SCRIPT_H

#include "headerFiles/ScriptingInterface.h"
#include <QDockWidget>

class Script : public QDockWidget
{
    Q_OBJECT

public:
    Script(QWidget *parent = 0);
    ~Script();

    /**
      * Saves the window state to the settings.
      */
    void saveWindowState();

    /**
      * Returns a pointer to the scripting interface.
      */
    ScriptingInterface* scriptingInterface();

public slots:
    /**
      * Changes the language.
      */
    void changeLanguage();

private:
    /**
      * Construct script window.
      */
    void construct();

    struct
    {
        ScriptingInterface *scriptingInterface;
    } m;
};

#endif // SCRIPT_H
