#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

class UserInterface
{
	public:
	UserInterface() {}
	virtual ~UserInterface() {}

	virtual void information(std::string message) = 0;
};

#endif // USER_INTERFACE_H
