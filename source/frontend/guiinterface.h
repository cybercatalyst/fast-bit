#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "userinterface.h"
#include <iostream>
#include <QMainWindow>
#include <QTabWidget>

class GuiInterface : public UserInterface
{
public:
    GuiInterface();
    ~GuiInterface();

    void information(std::string message);
    void message(std::string message);

private:
    void setUpInterface();

    QMainWindow* mainWindow;
    QTabWidget* tabWidget;
};

#endif // GUI_INTERFACE_H
