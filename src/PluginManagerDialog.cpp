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
#include <QMessageBox>

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

    ui->treeView->setHeaderHidden(true);
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

    if(!selectedFile.isEmpty())
    if(!PluginManager::instance().loadPlugin(selectedFile))
        QMessageBox::information(this, "Loading Plugin Failed", PluginManager::instance().errorString());

}

void PluginManagerDialog::updateConfiguration()
{
    model.clear();
    QList<QString> plugins = PluginManager::instance().availablePlugins();
    foreach(QString plugin, plugins)
    {
        QStandardItem* pluginItem = new QStandardItem(plugin);
        QFont font = pluginItem->font();
        font.setBold(true);
        pluginItem->setFont(font);

        model.appendRow(pluginItem);

        foreach(QString function, PluginManager::instance().availableFunctions(plugin))
        {
            pluginItem->appendRow(new QStandardItem(function));
        }
    }
    ui->treeView->setModel(&model);
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
