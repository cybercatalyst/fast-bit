#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

class PluginManager
{
public:
    static PluginManager& instance();

private:
    PluginManager();
    ~PluginManager();

    static PluginManager singleton;
};

#endif // PLUGIN_MANAGER_H
