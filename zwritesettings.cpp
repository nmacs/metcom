#include "zwritesettings.h"

ZWriteSettings::ZWriteSettings(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent),
	m_singleMode(true)
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
    int index;
    int count;

    reportProgress(0, tr("Writing settings to modem..."));

    ZSettings::Map const& map = m_settings.values();
    ZSettings::Map::const_iterator iter;

    count = map.size();
    for (iter = map.cbegin(), index = 0; iter != map.cend(); iter++, index++)
    {
		if (m_singleMode)
		{
			packet = QString("PUT=%1;%2=%3\r").arg(password()).arg(iter.key()).arg(iter.value().toString());
			res = execute(packet);
			if (!res)
			{
				return false;
			}
			packet.clear();

			reportProgress((double)index / count, "");
		}
		else
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

				reportProgress((double)index / count, "");
			}

			if (packet.isEmpty())
			{
				packet = QString("PUT=%1;").arg(password());
			}

			packet.append(pair);
		}
    }

	if (m_singleMode)
	{
		packet = QString("SAVE=%1\r").arg(password());
		res = execute(packet);
		if (!res)
		{
			return false;
		}
	}
	else
	{
		if (!packet.isEmpty())
		{
			packet.append('#');
			res = execute(packet);
			if (!res)
			{
				return false;
			}
		}
	}

    return true;
}
