#include "headerFiles/PluginManager.h"
#include "ui_PluginManager.h"

PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManager)
{
    ui->setupUi(this);
}

PluginManager::~PluginManager()
{
    delete ui;
}

void PluginManager::changeEvent(QEvent *e)
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
