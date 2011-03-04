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

#include <QtGui/QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QSettings>
#include <QTest>
#include <QTranslator>
#include <QDir>
#include "headerFiles/Main.h"
#include "headerFiles/MainWindow.h"
#include "headerFiles/renderers/HistogramOpenGLRenderer.h"

int main(int argc, char *argv[])
{
    Main::instance()->initialize(argc, argv);

    QSplashScreen splashScreen(QPixmap("media/fastBitLogo.png"));

    MainWindow mainWindow;
    mainWindow.restoreState(Main::instance()->settings()->value("mainWindowState").toByteArray());
    mainWindow.show();

    // Show splash screen and wait 1000 ms. qWait does not block the thread.
    splashScreen.show();
    QTest::qWait(1000);
    splashScreen.close();

    Main::instance()->application()->exec();

    Main::instance()->settings()->setValue("mainWindowState", mainWindow.saveState());
    mainWindow.saveWindowStates();
    Main::instance()->settings()->sync();
    return 0;
}

Main* Main::instance()
{
    static Main singleton;
    return &singleton;
}

void Main::initialize(int argc, char **argv)
{
    m.application = new QApplication(argc, argv);
    m.translator = new QTranslator();
    m.settings = new QSettings(QDir::homePath() + "/.fast-bit", QSettings::IniFormat);
    setLanguage(m.settings->value("language").toString());
}

void Main::setMainWindow(MainWindow *mainWindow)
{
    m.mainWindow = mainWindow;
}

void Main::setLanguage(QString language)
{
    if(language.isEmpty())
        language = "english";
    m.settings->setValue("language", language);
    m.translator->load("translations/fast-bit_" + language);
    emit languageChanged();
}

QString Main::translate(QString context, QString text)
{
    QString translatedText = m.translator->translate(context.toStdString().c_str(),
                                                     text.toStdString().c_str());
    if(translatedText.isEmpty())
        return text;
    return translatedText;
}

QSettings* Main::settings()
{
    return m.settings;
}

QApplication* Main::application()
{
    return m.application;
}

MainWindow* Main::mainWindow()
{
    return m.mainWindow;
}

Main::Main()
{
}

Main::~Main()
{
}
