#include "headerFiles/PluginManagerDialog.h"
#include "ui_PluginManagerDialog.h"
#include <QFileDialog>
#include <QApplication>
#include <QLibrary>

#include <list>
#include <string>
using namespace std;

PluginManagerDialog::PluginManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginManagerDialog)
{
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadPlugin()));
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
    if(selectedFile.length())
    {
        QLibrary library(selectedFile);
        typedef list<string> (*ContentFunction)();
        ContentFunction content = (ContentFunction) library.resolve("content");
        if(content)
        {
            qDebug("Plugin is valid, querying for content.");
            list<string> libraryContent = content();
            list<string>::iterator it = libraryContent.begin();
            while(it != libraryContent.end())
            {
                qDebug("Trying to load function %s.", (*it).c_str());
                it++;
            }
        }
        else
        {
            qDebug("Plugin is not valid.");
            // This is no a valid plugin.
        }
    }
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
