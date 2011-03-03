#ifndef MISC_H
#define MISC_H

#include "extension.h"

class Misc : public Extension
{
public:
    string name() { return "Misc"; }
    string version() { return "0.1"; }
};

#endif // MISC_H
