#ifndef CRYPTOGRAPHIC_H
#define CRYPTOGRAPHIC_H

#include "extension.h"

class Cryptographic : public Extension
{
public:
    string name() { return "Cryptographic"; }
    string version() { return "0.1"; }
};

#endif // CRYPTOGRAPHIC_H
