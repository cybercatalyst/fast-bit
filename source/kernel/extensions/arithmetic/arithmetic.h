#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "extension.h"

class Arithmetic : public Extension
{
public:
    Arithmetic();
    ~Arithmetic();

    string name() { return "Arithmetic"; }
    string version() { return "0.1"; }
};

#endif // ARITHMETIC_H
