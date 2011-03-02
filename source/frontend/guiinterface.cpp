#include "guiinterface.h"
#include <QMessageBox>

GuiInterface::GuiInterface()
{
    std::cout << "Constructing GUI Interface." << std::endl;
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
