#include "kernel.h"
#include "genericcontroller.h"

Controller& Kernel::controller()
{
        static GenericController genericController;
        return genericController;
}
