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

#include "headerFiles/ScriptEdit.h"
#include <QKeyEvent>

ScriptEdit::ScriptEdit(ScriptEngine *scriptEngine, QWidget *parent)
    : QTextEdit(parent)
{
    document()->setDefaultFont(QFont("Courier", 11, -1, false));
    setTabStopWidth(32);
    setLineWrapMode(QTextEdit::NoWrap);

    m.syntaxHighlighter = new SyntaxHighlighter(document());
    m.scriptEngine = scriptEngine;
    m.suggesting = false;
}

ScriptEdit::~ScriptEdit()
{

}

void ScriptEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Period)
    {

    }
    QTextEdit::keyPressEvent(e);
}
