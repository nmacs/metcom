#include "zsettings.h"
#include "zsettingsview.h"
#include <QDebug>
#include <QSettings>
#include <QFileInfo>

ZSettings::ZSettings(QObject *parent) :
    QObject(parent),
    m_view(0)
{
}

void ZSettings::operator=(const ZSettings &other)
{
    m_values = other.m_values;
    if (m_view)
    {
        m_view->draw(this);
    }
}

bool ZSettings::save(const QString &file)
{
    QSettings iniFile(file, QSettings::IniFormat);
    if (iniFile.status() != QSettings::NoError)
    {
        return false;
    }

    Map::const_iterator iter;
    for (iter = m_values.cbegin(); iter != m_values.cend(); ++iter)
    {
        iniFile.setValue(iter.key(), iter.value());
    }

    switch (iniFile.status())
    {
    case QSettings::AccessError:
        return false;
    case QSettings::FormatError:
        return false;
    case QSettings::NoError:
        return true;
    }

    return true;
}

bool ZSettings::load(const QString &file)
{
    QFileInfo fileInfo(file);

    if (!fileInfo.exists() || !fileInfo.isFile())
    {
        return false;
    }

    QSettings iniFile(file, QSettings::IniFormat);
    if (iniFile.status() != QSettings::NoError)
    {
        return false;
    }

    m_values.clear();

    QStringList keys = iniFile.allKeys();
    QStringList::const_iterator iter;
    for (iter = keys.cbegin(); iter != keys.cend(); ++iter)
    {
        m_values.insert(*iter, iniFile.value(*iter));
    }

    if (m_view)
    {
        m_view->draw(this);
    }

    return true;
}

void ZSettings::setValues(const ZSettings::Map &values)
{
    m_values = values;
    if (m_view)
    {
        m_view->draw(this);
    }
}

void ZSettings::setValue(const QString &key, const QVariant &value)
{
    m_values.insert(key, value);
    if (m_view)
    {
        m_view->draw(this);
    }
}

const QVariant &ZSettings::value(const QString &key, QVariant const& def) const
{
    Map::const_iterator item = m_values.find(key);
    return item != m_values.end() ? item.value() : def;
}

void ZSettings::clear()
{
    m_values.clear();
}

void ZSettings::setView(ZSettingsView *view)
{
    m_view = view;
    connect(m_view, SIGNAL(updated(QString,QVariant)),
            this, SLOT(update(QString,QVariant)));

    view->draw(this);
}

void ZSettings::update(const QString &key, const QVariant &value)
{
    m_values.insert(key, value);
}
