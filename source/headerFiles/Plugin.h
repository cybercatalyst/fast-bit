#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>
#include <QList>

class Plugin
{
public:
    Plugin(){}
    ~Plugin(){}

    virtual QString identifier() = 0;
    virtual QList<QString> content() = 0;
private:

};

#endif // PLUGIN_H
