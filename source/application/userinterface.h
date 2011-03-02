#include <string>

class UserInterface
{
	public:
	UserInterface() {}
	virtual ~UserInterface() {}

	virtual void information(std::string message) = 0;
};
