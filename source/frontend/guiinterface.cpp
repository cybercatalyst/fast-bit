#include "guiinterface.h"

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
