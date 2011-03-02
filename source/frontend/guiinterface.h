#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "userinterface.h"
#include <iostream>

class GuiInterface : public UserInterface
{
	public:
        GuiInterface();
        ~GuiInterface();

        void information(std::string message);
        void message(std::string message);
};

#endif // GUI_INTERFACE_H
