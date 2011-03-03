#ifndef PHOTOGRAPHIC_H
#define PHOTOGRAPHIC_H

#include "extension.h"

class Photographic : public Extension
{
public:
    Photographic();
    ~Photographic();
    string name() { return "Photographic"; }
    string version() { return "0.1"; }
};

#endif // PHOTOGRAPHIC_H
