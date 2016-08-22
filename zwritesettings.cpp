#include "zwritesettings.h"

ZWriteSettings::ZWriteSettings(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent)
{
}

void ZWriteSettings::setSettings(const ZSettings &settings)
{
    m_settings = settings;
}

bool ZWriteSettings::doRun()
{
    bool res;
    QString packet;

    ZSettings::Map const& map = m_settings.values();
    ZSettings::Map::const_iterator iter;

    for (iter = map.cbegin(); iter != map.cend(); iter++)
    {
        QString pair = QString("%1=%2;").arg(iter.key()).arg(iter.value().toString());

        if (packet.length() + pair.length() >= 1024)
        {
            packet.append('*');
            res = execute(packet);
            if (!res)
            {
                return false;
            }
            packet.clear();
        }

        if (packet.isEmpty())
        {
            packet = QString("PUT=%1;").arg(password());
        }

        packet.append(pair);
    }

    if (!packet.isEmpty())
    {
        packet.append('#');
        res = execute(packet);
        if (!res)
        {
            return false;
        }
    }

    return true;
}
