#include "headerFiles/PluginManager.h"
#include <QLibrary>
#include <string>

using namespace std;
PluginManager PluginManager::singleton;

PluginManager::PluginManager()
    : QObject()
{

}

PluginManager::~PluginManager()
{

}

PluginManager& PluginManager::instance()
{
    return PluginManager::singleton;
}

void PluginManager::loadPlugin(QString fileName)
{
    if(fileName.length())
    {
        QLibrary library(fileName);
        typedef list<string> (*ContentFunction)();
        ContentFunction content = (ContentFunction) library.resolve("content");
        if(content)
        {
            qDebug("Plugin is valid, querying for content.");
            list<string> libraryContent = content();
            list<string>::iterator it = libraryContent.begin();
            while(it != libraryContent.end())
            {
                qDebug("Trying to load function %s.", (*it).c_str());
                it++;
            }
        }
        else
        {
            qDebug("Plugin is not valid.");
            // This is no a valid plugin.
        }
    }

    emit configurationChanged();
}
