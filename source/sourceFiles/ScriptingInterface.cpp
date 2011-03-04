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
#include "headerFiles/ScriptingInterface.h"
#include <QFileDialog>

#define FAST_BIT_SCRIPT ".fast-bit-script"

ScriptingInterface::ScriptingInterface(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("scriptingInterface");
    construct();

    connect(Main::instance(), SIGNAL(languageChanged()), this, SLOT(changeLanguage()));
    connect(m.scriptEngine, SIGNAL(output(QString)), this, SLOT(input(QString)));
    connect(m.runScript, SIGNAL(clicked()), this, SLOT(evaluateScript()));
    //connect(m.action["Open"], SIGNAL(triggered()), this, SLOT(openFile()));
    //connect(m.action["Save"], SIGNAL(triggered()), this, SLOT(saveFile()));
}

ScriptingInterface::~ScriptingInterface()
{
}

void ScriptingInterface::changeLanguage()
{
    //m.menu["File"]->setTitle(Main::instance()->translate("ScriptingInterface", "File"));
    m.runScript->setText(Main::instance()->translate("ScriptingInterface", "Run"));
    //m.action["Open"]->setText(Main::instance()->translate("ScriptingInterface", "Open"));
    //m.action["Save"]->setText(Main::instance()->translate("ScriptingInterface", "Save"));
}

void ScriptingInterface::evaluateScript()
{
    emit output(Main::instance()->translate("ScriptingInterface", "<b>Evaluating script..</b>"));
    QMetaObject::invokeMethod(m.scriptEngine, "evaluateScript", Qt::QueuedConnection,
                              Q_ARG(QString, m.scriptEdit->document()->toPlainText()));
}

void ScriptingInterface::input(QString message)
{
    emit output(message);
}

void ScriptingInterface::openFile()
{
    QString fileName =
    QFileDialog::getOpenFileName(this,
        Main::instance()->translate("ScriptingInterface", "Open Script File"),
        "examples/script",
        QString("*") + FAST_BIT_SCRIPT);

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        m.scriptEdit->setText(file.readAll());
        file.close();
    }
}

void ScriptingInterface::saveFile()
{
    QString fileName =
    QFileDialog::getSaveFileName(this,
        Main::instance()->translate("ScriptingInterface", "Save Script File"),
        "examples/script",
        QString("*") + FAST_BIT_SCRIPT);

    if(!fileName.endsWith(FAST_BIT_SCRIPT))
        fileName.append(FAST_BIT_SCRIPT);

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(m.scriptEdit->toPlainText().toLocal8Bit());
    file.close();
}

void ScriptingInterface::construct()
{
    //m.menu["File"] = menuBar()->addMenu(Main::instance()->translate("ScriptingInterface", "File"));
    //m.action["Open"] = m.menu["File"]->addAction(Main::instance()->translate("ScriptingInterface", "Open"));
    //m.action["Save"] = m.menu["File"]->addAction(Main::instance()->translate("ScriptingInterface", "Save"));

    m.controlBar = new QToolBar(Main::instance()->translate("ScriptingInterface", "Control"), this);
    m.runScript = new QPushButton(Main::instance()->translate("ScriptingInterface", "Run"), m.controlBar);
    m.controlBar->addWidget(m.runScript);

    m.controlBar->setObjectName("controlBar");
    addToolBar(m.controlBar);

    m.scriptEngine = new ScriptEngine();
    m.scriptEdit = new ScriptEdit(m.scriptEngine, this);
    setCentralWidget(m.scriptEdit);

    setWindowFlags(Qt::Widget);
}
