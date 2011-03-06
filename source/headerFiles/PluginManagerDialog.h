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
