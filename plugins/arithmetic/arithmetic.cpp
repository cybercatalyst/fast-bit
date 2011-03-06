#include "arithmetic.h"

Plugin* exportPlugin()
{
    Plugin* plugin = new PluginImpl();
    return plugin;
}

PluginImpl::PluginImpl()
{

}

PluginImpl::~PluginImpl()
{

}

QString PluginImpl::identifier()
{
    return "Arithmetic";
}

QList<QString> PluginImpl::content()
{
    QList<QString> contentList;
    contentList << "Add" << "Subtract" << "Multiplicate" << "Divide";
    return contentList;
}
