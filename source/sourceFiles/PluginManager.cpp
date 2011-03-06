#include "headerFiles/PluginManager.h"

PluginManager PluginManager::singleton;

PluginManager::PluginManager()
{

}

PluginManager::~PluginManager()
{

}

PluginManager& PluginManager::instance()
{
    return PluginManager::singleton;
}
