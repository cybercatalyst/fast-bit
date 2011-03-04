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

#ifndef SCRIPT_EDIT_H
#define SCRIPT_EDIT_H

#include <QTextEdit>
#include "headerFiles/SyntaxHighlighter.h"
#include "headerFiles/ScriptEngine.h"

class ScriptEdit : public QTextEdit
{
public:
    ScriptEdit(ScriptEngine *scriptEngine, QWidget *parent = 0);
    ~ScriptEdit();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    struct
    {
        ScriptEngine *scriptEngine;
        SyntaxHighlighter *syntaxHighlighter;
        bool suggesting;
    } m;
};

#endif // SCRIPT_EDIT_H