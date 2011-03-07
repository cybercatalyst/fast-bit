#include "arithmetic.h"

PluginImpl::PluginImpl(QObject* parent)
    : PluginInterface(parent)
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

Q_EXPORT_PLUGIN2(arithmetic, PluginImpl);
