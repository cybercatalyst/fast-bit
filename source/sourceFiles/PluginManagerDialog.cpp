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
