#ifndef KERNEL_H
#define KERNEL_H

#include "controller.h"
#include <list>

using namespace std;

class Kernel
{
public:
    static Controller& controller();

};

#endif // KERNEL_H
