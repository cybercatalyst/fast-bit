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

#include "headerFiles/PluginManagerDialog.h"
#include "ui_PluginManagerDialog.h"
#include "headerFiles/PluginManager.h"
#include <QFileDialog>
#include <QApplication>

#include <list>
#include <string>
using namespace std;

PluginManagerDialog::PluginManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManagerDialog)
{
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadPlugin()));

    connect(&PluginManager::instance(), SIGNAL(configurationChanged()), this, SLOT(updateConfiguration()));
    updateConfiguration();
}

PluginManagerDialog::~PluginManagerDialog()
{
    delete ui;
}

void PluginManagerDialog::loadPlugin()
{
    QString selectedFile =
    QFileDialog::getOpenFileName(this,
                                 "Load Plugin",
                                 QApplication::applicationDirPath() + "/plugins");
    PluginManager::instance().loadPlugin(selectedFile);
}

void PluginManagerDialog::updateConfiguration()
{

}

void PluginManagerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
