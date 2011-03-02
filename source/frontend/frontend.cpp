#include "frontend.h"
#include "guiinterface.h"

UserInterface& Frontend::userInterface()
{
	static GuiInterface guiInterface;
	return guiInterface;
}
