#ifndef FRONTEND_H
#define FRONTEND_H

#include "userinterface.h"
class Frontend
{
	public:
	static const int moduleId = 1;
	static UserInterface& userInterface();
};

#endif // FRONTEND_H
