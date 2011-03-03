#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    Controller() {}
    virtual ~Controller() {}

    virtual void boot() = 0;
};

#endif // CONTROLLER_H
