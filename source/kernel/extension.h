#ifndef EXTENSION_H
#define EXTENSION_H

#include <string>

using namespace std;

/**
  * Declares the extension interface.
  */
class Extension
{
public:
    Extension();
    ~Extension();

    virtual string name() = 0;
    virtual string version() = 0;
};

#endif // EXTENSION_H
