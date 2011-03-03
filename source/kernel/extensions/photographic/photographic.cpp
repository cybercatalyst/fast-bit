#include "photographic.h"
#include "frontend.h"

Photographic::Photographic()
{
    Frontend::userInterface().information("Preparing extension: " + name());
}

Photographic::~Photographic()
{

}
