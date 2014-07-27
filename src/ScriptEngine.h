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

#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <QThread>
#include <QScriptEngine>

class ScriptEngine : public QScriptEngine
{
    Q_OBJECT

public:
    ScriptEngine();
    ~ScriptEngine();

public slots:
    void include(QString includeFile);
    void system(QString command);
    void writeln(QString message);
    unsigned int red(unsigned int color);
    unsigned int green(unsigned int color);
    unsigned int blue(unsigned int color);
    unsigned int rgb(unsigned int r, unsigned int g, unsigned int b);
    unsigned int rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
    double sin(double x);
    double cos(double x);
    double tan(double x);

private slots:
    void evaluateScript(QString script);
    void handleException(const QScriptValue& exception);

signals:
    void output(QString message);
};

#endif // SCRIPT_ENGINE_H
