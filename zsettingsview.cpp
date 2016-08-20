#include "zsettingsview.h"

ZSettingsView::ZSettingsView(QObject *parent) : QObject(parent)
{
}

void ZSettingsView::emitUpdated(const QString &key, const QVariant &value)
{
    emit updated(key, value);
}
