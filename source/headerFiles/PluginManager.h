#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "headerFiles/Plugin.h"
#include <QString>
#include <QObject>

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager& instance();

    void loadPlugin(QString fileName);

signals:
    void configurationChanged();

private:
    PluginManager();
    ~PluginManager();

    static PluginManager singleton;
};

#endif // PLUGIN_MANAGER_H
