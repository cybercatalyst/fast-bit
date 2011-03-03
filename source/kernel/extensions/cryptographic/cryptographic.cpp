#include "cryptographic.h"
#include "frontend.h"

Cryptographic::Cryptographic()
{
    Frontend::userInterface().information("Preparing extension: " + name());
}

Cryptographic::~Cryptographic()
{

}
