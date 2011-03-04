#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>

namespace Ui {
    class PluginManager;
}

class PluginManager : public QDialog {
    Q_OBJECT
public:
    PluginManager(QWidget *parent = 0);
    ~PluginManager();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PluginManager *ui;
};

#endif // PLUGINMANAGER_H
