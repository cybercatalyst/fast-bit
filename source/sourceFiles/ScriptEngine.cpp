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
#include "headerFiles/ScriptEngine.h"
#include "headerFiles/scriptClasses/ScriptImage.h"
#include "headerFiles/scriptClasses/ScriptVectorImage.h"
#include "headerFiles/scriptClasses/ScriptFile.h"
#include <QFile>
#include <QScriptProgram>
#include <math.h>

// This hack is needed so we can name the slots like they are usually called.
// Otherwise these slots would call themselves which would lead to infinite recursion.
double sin_wrapper(double x) { return sin(x); }
double cos_wrapper(double x) { return cos(x); }
double tan_wrapper(double x) { return tan(x); }
void system_wrapper(QString command) { system(command.toStdString().c_str()); }

Q_SCRIPT_DECLARE_QMETAOBJECT(ScriptImage, QObject*)
Q_SCRIPT_DECLARE_QMETAOBJECT(ScriptVectorImage, QObject*)
Q_SCRIPT_DECLARE_QMETAOBJECT(ScriptFile, QObject*)

ScriptEngine::ScriptEngine()
    : QScriptEngine()
{
    workerThread = new QThread();
    workerThread->start();
    moveToThread(workerThread);

    setGlobalObject(newQObject(this));

    QScriptValue scriptImageClass = this->scriptValueFromQMetaObject<ScriptImage>();
    QScriptValue scriptVectorImageClass = this->scriptValueFromQMetaObject<ScriptVectorImage>();
    QScriptValue scriptFileClass = this->scriptValueFromQMetaObject<ScriptFile>();

    globalObject().setProperty("Image", scriptImageClass);
    globalObject().setProperty("VectorImage", scriptVectorImageClass);
    globalObject().setProperty("File", scriptFileClass);

    connect(this, SIGNAL(signalHandlerException(const QScriptValue&)),
            this, SLOT(handleException(const QScriptValue&)));
}

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::include(QString includeFile)
{
    QFile file(includeFile);
    file.open(QFile::ReadOnly);
    evaluate(file.readAll());
    file.close();
}

void ScriptEngine::system(QString command)
{
    system_wrapper(command);
}

void ScriptEngine::writeln(QString message)
{
    emit output(message);
}

unsigned int ScriptEngine::red(unsigned int color)
{
    return qRed(color);
}

unsigned int ScriptEngine::green(unsigned int color)
{
    return qGreen(color);
}

unsigned int ScriptEngine::blue(unsigned int color)
{
    return qBlue(color);
}

unsigned int ScriptEngine::rgb(unsigned int r, unsigned int g, unsigned int b)
{
    return qRgb(r, g, b);
}

unsigned int ScriptEngine::rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return qRgba(r, g, b, a);
}

double ScriptEngine::sin(double x)
{
    return sin_wrapper(x);
}

double ScriptEngine::cos(double x)
{
    return cos_wrapper(x);
}

double ScriptEngine::tan(double x)
{
    return tan_wrapper(x);
}

void ScriptEngine::evaluateScript(QString script)
{
    emit output(Main::instance().translate("ScriptEngine", "Precompiling script.."));
    QScriptProgram program(script);
    QScriptValue result = evaluate(program);
    emit output(Main::instance().translate("ScriptEngine", "<b>Script finished and returned %1.</b>").arg(result.toString()));
}

void ScriptEngine::handleException(const QScriptValue& exception)
{
    emit output(exception.toString());
}
