#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "userinterface.h"

class GuiInterface : public UserInterface
{
	public:
	GuiInterface() {}
	~GuiInterface() {}

	void information(std::string message) {}
};

#endif // GUI_INTERFACE_H
