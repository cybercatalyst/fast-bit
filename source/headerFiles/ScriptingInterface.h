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

#ifndef SCRIPTING_INTERFACE_H
#define SCRIPTING_INTERFACE_H

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMap>
#include <QToolBar>
#include <QMainWindow>
#include <QPushButton>

#include "headerFiles/ScriptEngine.h"
#include "headerFiles/ScriptEdit.h"

class ScriptingInterface : public QWidget
{
    Q_OBJECT

public:
    ScriptingInterface(QWidget *parent = 0);
    ~ScriptingInterface();

public slots:
    /**
      * Changes the language.
      */
    void changeLanguage();

    /**
      * Evaluates the script.
      */
    void evaluateScript();

public slots:
    /**
      * Input for messages that should be forwarded.
      */
    void input(QString message);

private slots:
    /**
      * Opens an open file dialog and loads the selected file.
      */
    void openFile();

    /**
      * Opens a save file dialog and saves the selected file.
      */
    void saveFile();

signals:
    /**
      * Messages that have to be displayed somewhere.
      */
    void output(QString text);

private:
    /**
      * Construct scripting interface.
      */
    void construct();

    struct
    {
        QToolBar *controlBar;
        QPushButton *runScript;
        ScriptEdit *scriptEdit;
        ScriptEngine *scriptEngine;

        /**
          * QString to QMenu*-map for main window.
          */
        QMap<QString, QMenu*> menu;

        /**
          * QString to QAction*-map for main window.
          */
        QMap<QString, QAction*> action;
    } m;
};

#endif // SCRIPTING_INTERFACE_H
