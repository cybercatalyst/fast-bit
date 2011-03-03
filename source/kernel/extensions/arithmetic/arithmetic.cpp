#include "arithmetic.h"
#include "frontend.h"

Arithmetic::Arithmetic()
{
    Frontend::userInterface().information("Preparing extension: " + name());
}

Arithmetic::~Arithmetic()
{

}
