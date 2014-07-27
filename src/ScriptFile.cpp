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

#include "ScriptFile.h"

ScriptFile::ScriptFile(QObject *parent)
    : QObject(parent)
{
}

ScriptFile::~ScriptFile()
{
}

bool ScriptFile::open(QString fileName)
{
    file.setFileName(fileName);
    file.open(QFile::ReadWrite);
}

void ScriptFile::close()
{
    file.close();
}

void ScriptFile::write(QString content)
{
    file.write(content.toLocal8Bit());
}
