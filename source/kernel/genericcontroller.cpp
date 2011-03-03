#include "genericcontroller.h"
#include "frontend.h"

GenericController::GenericController()
{
}

GenericController::~GenericController()
{
}

void GenericController::boot()
{
    Frontend::userInterface().information("Preparing kernel.");
}
