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

#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QObject>
#include <QString>

class MainWindow;
class Main : public QObject
{
    Q_OBJECT
    public:
        static Main* instance();
        void initialize(int argc, char** argv);

        void setMainWindow(MainWindow* mainWindow);
        void setLanguage(QString language);
        QString translate(QString context, QString text);

        QSettings* settings();
        QApplication* application();
        MainWindow* mainWindow();

    signals:
        void languageChanged();

    private:
        Main();
        ~Main();

        struct
        {
            MainWindow* mainWindow;
            QTranslator* translator;
            QApplication* application;
            QSettings* settings;
        } m;
 };

#endif // MAIN_H
