#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "headerFiles/Plugin.h"
extern "C"
{
    Plugin* exportPlugin();
}

class PluginImpl : public Plugin
{
public:
    PluginImpl();
    ~PluginImpl();

    QString identifier();
    QList<QString> content();
};

#endif // ARITHMETIC_H
