#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "userinterface.h"
#include <iostream>
#include <QMainWindow>

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
};

#endif // GUI_INTERFACE_H
