#include "zsettings.h"
#include "zsettingsview.h"
#include <QDebug>
#include <QSettings>
#include <QFileInfo>

#define CONFIG_METCOM_ETHERNET

ZSettings::ZSettings(QObject *parent) :
    QObject(parent),
	m_locked(false)
{
}

const ZSettings &ZSettings::defaultSettings()
{
    static ZSettings settings;
    static bool initialized = false;

    if (!initialized)
    {
#ifndef CONFIG_METCOM_ETHERNET
        settings.setValue("TSIM", 0);
        settings.setValue("SWAP", 10);
        settings.setValue("RMNS", 10);
        settings.setValue("APN1", "");
        settings.setValue("LOG1", "");
        settings.setValue("PSW1", "");
        settings.setValue("PIN1", "");
        settings.setValue("OFF1", 1);
        settings.setValue("NET1", 0);
        settings.setValue("ROA1", 1);
        settings.setValue("APN2", "");
        settings.setValue("LOG2", "");
        settings.setValue("PSW2", "");
        settings.setValue("PIN2", "");
        settings.setValue("OFF2", 0);
        settings.setValue("NET2", 0);
        settings.setValue("ROA2", 1);
        settings.setValue("MODE", 0);
        settings.setValue("APHN", 1);
        settings.setValue("GCSD", 0);
        settings.setValue("IPC1", "");
        settings.setValue("PTC1", "");
        settings.setValue("IPC2", "");
        settings.setValue("PTC2", "");
        settings.setValue("PTSR", 9000);
        settings.setValue("EIP1", "");
        settings.setValue("EIP2", "");
        settings.setValue("EIP3", "");
        settings.setValue("EIP4", "");
        settings.setValue("ESCH", 0);
        settings.setValue("SCH1", "yandex.ru:8080");
        settings.setValue("SCH2", "8.8.8.8:8080");
        settings.setValue("EPNG", 1);
        settings.setValue("IPP1", "yandex.ru");
        settings.setValue("IPP2", "google.ru");
        settings.setValue("EDNS", 1);
        settings.setValue("PPNG", 10);
        settings.setValue("MPSZ", 1024);
        settings.setValue("TRDT", 300);
        settings.setValue("SITT", 600);
        settings.setValue("MPRT", 0);
        settings.setValue("MAPT", 1);
        settings.setValue("BDRT", 4);
        settings.setValue("BITS", 3);
        settings.setValue("PRTY", 4);
        settings.setValue("SSTB", 0);
		settings.setValue("DTAD", 1);

        for (int i = 0; i < 10; i++)
        {
            settings.setValue(QString("PHN%0").arg(i), "+7");
            settings.setValue(QString("GRP%0").arg(i), "0000000000");
        }

        settings.setValue("DBEN", 1);
        settings.setValue("DBMD", 1);
        settings.setValue("DBIP", "");
        settings.setValue("DBPC", 9001);
        settings.setValue("DBPS", 9001);
        settings.setValue("DBAF", 0);
        settings.setValue("DBPG", 1);

        settings.setValue("RSIT", 1);
        settings.setValue("RSHR", 24);
        settings.setValue("RSDT", 1);
        settings.setValue("DTHR", 16);
        settings.setValue("DTMN", 30);
        settings.setValue("GPHR", 2);
		settings.setValue("NTPE", 0);
		settings.setValue("NTP1", "ntp2.stratum2.ru:123");
		settings.setValue("NTP2", "ntp3.stratum2.ru:123");
		settings.setValue("NTP3", "ntp4.stratum2.ru:123");
		settings.setValue("NTPZ", "+12");

		settings.setValue("WMMD", 0);
		settings.setValue("WMTP", 0);
		settings.setValue("WMWT", "01:00");
		settings.setValue("WMON", "06:00");
		settings.setValue("WME1", "0:00:00:00");
		settings.setValue("WME2", "0:00:00:00");
		settings.setValue("WME3", "0:00:00:00");
		settings.setValue("WME4", "0:00:00:00");
		settings.setValue("WME5", "0:00:00:00");
		settings.setValue("WMES", 0);
		settings.setValue("WMGI", 3);
		settings.setValue("WMIS", 0);
		settings.setValue("WMGO", 4);
		settings.setValue("WMSI", "start");
		settings.setValue("WMSO", "stop");
		settings.setValue("WMIT", 10);
#else
		settings.setValue("DHCP", 1);
		settings.setValue("MAC", "1E:30:6C:00:00:00");
		settings.setValue("LOCALIP", "192.168.1.200");
		settings.setValue("SUBMASK", "255.255.255.0");
		settings.setValue("DEFGWAY", "192.168.1.1");
		settings.setValue("PRIDNS", "192.168.1.1");
		settings.setValue("SECDNS", "192.168.1.1");
		settings.setValue("MODE", 1);
		settings.setValue("SPORT", 9000);

		settings.setValue("ENIP1", "0.0.0.0");
		settings.setValue("ENIP2", "0.0.0.0");
		settings.setValue("ENIP3", "0.0.0.0");
		settings.setValue("ENIP4", "0.0.0.0");
		settings.setValue("IP1", "");
		settings.setValue("PORT1", 9000);
		settings.setValue("IP2", "");
		settings.setValue("PORT2", 9002);
		settings.setValue("ENPING", 1);
		settings.setValue("PINGIP1", "8.8.8.8");

		settings.setValue("PINGIP2", "yandex.ru");
		settings.setValue("PINGDNS", 1);
		settings.setValue("TIMEPING", 10);
		settings.setValue("ENDBG", 1);
		settings.setValue("MODEDBG", 1);
		settings.setValue("IPDBG", "");
		settings.setValue("PORTDBG", 9001);
		settings.setValue("PORTSDBG", 9001);
		settings.setValue("MPSIZE", 1024);
		settings.setValue("TOUT", 500);

		settings.setValue("SITOUT", 600);
		settings.setValue("INTTIM", 1);
		settings.setValue("PINTTIM", 24);
		settings.setValue("DLYTIM", 0);
		settings.setValue("HOURTIM", 23);
		settings.setValue("MINTIM", 59);
		settings.setValue("ENNTP", 0);
		settings.setValue("NTP1", "ntp2.stratum2.ru");
		settings.setValue("NTP2", "ntp3.stratum2.ru");
		settings.setValue("NTP3", "ntp4.stratum2.ru");

		settings.setValue("TZONE", "+12");
		settings.setValue("BDRT", 5);
		settings.setValue("SETUART", 0);
		settings.setValue("PORTTN", 23);
#endif

        initialized = true;
    }

    return settings;
}

void ZSettings::drawViews(ZSettingsView *except)
{
    QList<ZSettingsView*>::iterator iter, end;
    end = m_views.end();
    for (iter = m_views.begin(); iter != end; ++iter)
    {
        if (*iter != except)
        {
            (*iter)->draw(this);
        }
    }
}

void ZSettings::operator=(const ZSettings &other)
{
    m_values = other.m_values;
    drawViews();
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

    drawViews();

    return true;
}

void ZSettings::setValues(const ZSettings::Map &values)
{
    m_values = values;
    drawViews();
}

void ZSettings::setValue(const QString &key, const QVariant &value)
{
    m_values.insert(key, value);
    drawViews();
}

void ZSettings::setValidator(QValidator *validator)
{
    validator->setParent(this);
}

const QVariant &ZSettings::value(const QString &key, QVariant const& def) const
{
    Map::const_iterator item = m_values.find(key);
    return item != m_values.end() ? item.value() : def;
}

void ZSettings::redraw()
{
	drawViews();
}

void ZSettings::clear()
{
    m_values.clear();
}

void ZSettings::addView(ZSettingsView *view)
{
    m_views.push_back(view);
    connect(view,
            &ZSettingsView::updated,
            this,
            &ZSettings::update);

    view->draw(this);
}

void ZSettings::update(ZSettingsView *sender, const QString &key, const QVariant &value)
{
	if (m_locked)
		return;

    m_values.insert(key, value);
    drawViews(sender);
}
