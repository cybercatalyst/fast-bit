#ifndef GENERIC_CONTROLLER_H
#define GENERIC_CONTROLLER_H

#include "kernel.h"
#include "controller.h"
#include "extension.h"
#include <list>

class GenericController : public Controller
{
public:
    GenericController();
    ~GenericController();

    void boot();

private:
    list<Extension*> extensions;
};

#endif // GENERIC_CONTROLLER_H
