#include "guiinterface.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QPushButton>

GuiInterface::GuiInterface()
{
    std::cout << "Constructing GUI Interface." << std::endl;
    setUpInterface();
}

GuiInterface::~GuiInterface()
{
    std::cout << "Destroying GUI Interface." << std::endl;
}

void GuiInterface::information(std::string message)
{
    std::cout << message << std::endl;
}

void GuiInterface::message(std::string message)
{
    QMessageBox::information(0, "Message", QString(message.c_str()), QMessageBox::Ok);
}

void GuiInterface::setUpInterface()
{
    mainWindow = new QMainWindow();
    mainWindow->setCentralWidget(new QTextEdit());
    QToolBar* mainToolBar = mainWindow->addToolBar("test");
    mainToolBar->addWidget(new QPushButton("Hallo2"));
    mainWindow->menuBar()->addMenu("Test");

    mainWindow->showMaximized();
}
