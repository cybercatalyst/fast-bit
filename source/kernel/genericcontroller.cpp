#include "genericcontroller.h"
#include "frontend.h"

#include "extensions/arithmetic/arithmetic.h"
#include "extensions/cryptographic/cryptographic.h"
#include "extensions/photographic/photographic.h"
#include "extensions/misc/misc.h"

GenericController::GenericController()
{
}

GenericController::~GenericController()
{
}

void GenericController::boot()
{
    Frontend::userInterface().information("Preparing kernel.");
    extensions.push_back(new Arithmetic());
    extensions.push_back(new Cryptographic());
    extensions.push_back(new Photographic());
    extensions.push_back(new Misc());
}
