#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "headerFiles/PluginInterface.h"
#include <QtPlugin>

class PluginImpl : public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
public:
    PluginImpl(QObject* parent = 0);

    QString identifier();
    QList<QString> content();
};

#endif // ARITHMETIC_H
