#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

class UserInterface
{
public:
    UserInterface() {}
    virtual ~UserInterface() {}

    /**
      * Hands over a message to the user, but does not necessarily prompt him.
      */
    virtual void information(std::string message) = 0;

    /**
      * Hands over a message to the user and expects him to read the message.
      */
    virtual void message(std::string message) = 0;
};

#endif // USER_INTERFACE_H
