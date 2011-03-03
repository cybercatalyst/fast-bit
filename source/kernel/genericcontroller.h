#ifndef GENERIC_CONTROLLER_H
#define GENERIC_CONTROLLER_H

#include "controller.h"

class GenericController : public Controller
{
public:
    GenericController();
    ~GenericController();

    void boot();
};

#endif // GENERIC_CONTROLLER_H
