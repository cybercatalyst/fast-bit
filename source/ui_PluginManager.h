/********************************************************************************
** Form generated from reading UI file 'PluginManager.ui'
**
** Created: Fri Mar 4 20:45:41 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINMANAGER_H
#define UI_PLUGINMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_PluginManager
{
public:
    QTreeView *treeView;
    QPushButton *loadButton;
    QPushButton *closeButton;
    QPushButton *unloadButton;

    void setupUi(QDialog *PluginManager)
    {
        if (PluginManager->objectName().isEmpty())
            PluginManager->setObjectName(QString::fromUtf8("PluginManager"));
        PluginManager->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PluginManager->sizePolicy().hasHeightForWidth());
        PluginManager->setSizePolicy(sizePolicy);
        PluginManager->setMinimumSize(QSize(400, 300));
        PluginManager->setMaximumSize(QSize(400, 300));
        PluginManager->setModal(false);
        treeView = new QTreeView(PluginManager);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 10, 381, 251));
        loadButton = new QPushButton(PluginManager);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(10, 270, 105, 24));
        closeButton = new QPushButton(PluginManager);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(280, 270, 105, 24));
        unloadButton = new QPushButton(PluginManager);
        unloadButton->setObjectName(QString::fromUtf8("unloadButton"));
        unloadButton->setGeometry(QRect(120, 270, 105, 24));

        retranslateUi(PluginManager);
        QObject::connect(closeButton, SIGNAL(clicked()), PluginManager, SLOT(close()));

        QMetaObject::connectSlotsByName(PluginManager);
    } // setupUi

    void retranslateUi(QDialog *PluginManager)
    {
        PluginManager->setWindowTitle(QApplication::translate("PluginManager", "Dialog", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("PluginManager", "Load", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("PluginManager", "Close", 0, QApplication::UnicodeUTF8));
        unloadButton->setText(QApplication::translate("PluginManager", "Unload", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PluginManager: public Ui_PluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINMANAGER_H
