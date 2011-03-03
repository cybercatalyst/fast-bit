#include "misc.h"
#include "frontend.h"

Misc::Misc()
{
    Frontend::userInterface().information("Preparing extension: " + name());
}

Misc::~Misc()
{

}
