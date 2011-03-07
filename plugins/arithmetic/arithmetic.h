#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "headerFiles/Plugin.h"
#include <QObject>

extern "C"
{
    Plugin* exportPlugin();
}

class ObjectInterfaceProxy : public QObject
{
    Q_OBJECT
public:
    ObjectInterfaceProxy() : QObject() {}
    ~ObjectInterfaceProxy() {}
};

class PluginImpl : public Plugin
{
public:
    PluginImpl();
    ~PluginImpl();

    QString identifier();
    QList<QString> content();
    ObjectInterfaceProxy objectInterfaceProxy;
};

#endif // ARITHMETIC_H
