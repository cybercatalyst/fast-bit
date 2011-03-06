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

#ifndef PLUGIN_MANAGER_DIALOG_H
#define PLUGIN_MANAGER_DIALOG_H

#include <QDialog>

namespace Ui {
    class PluginManagerDialog;
}

class PluginManagerDialog : public QDialog {
    Q_OBJECT
public:
    PluginManagerDialog(QWidget *parent = 0);
    ~PluginManagerDialog();

public slots:
    void loadPlugin();
    void updateConfiguration();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PluginManagerDialog *ui;
};

#endif // PLUGIN_MANAGER_DIALOG_H
