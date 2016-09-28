#include "zchannelcsd.h"
#include <QThread>
#include <QDebug>

#include "zprotocol.h"

ZChannelCSD::ZChannelCSD(QObject *parent) : ZChannelDirectSerial(parent)
{
}

ZChannelCSD::~ZChannelCSD()
{
	disconnect();
}

bool ZChannelCSD::dialup()
{
	char input_buffer[128];

	QString atd = QString("ATD%1\r").arg(m_phone);
	write(atd.toLatin1().constData(), atd.length(), 200);

	while (1)
	{
		qint64 r = read(input_buffer, sizeof(input_buffer), 60000);
		if (r < 0)
		{
			setErrorString(QString(tr("No response from local modem: %1")).arg(errorString()));
			return false;
		}

		if (r >= 7 && memcmp(input_buffer, "CONNECT", 7) == 0)
		{
			return true;
		}
	}

	return false;
}

bool ZChannelCSD::connect()
{
    bool res;

	if (isConnected())
		return true;

    res = m_port->open(QIODevice::ReadWrite);
    if (!res)
    {
        setErrorString(m_port->errorString());
        return false;
    }

	m_port->setParity(QSerialPort::NoParity);
	m_port->setDataBits(QSerialPort::Data8);
	m_port->setStopBits(QSerialPort::OneStop);
	m_port->setFlowControl(QSerialPort::NoFlowControl);

	if (m_progress)
	{
		m_progress->start();
		m_progress->setProgress(-1, tr("Connecting..."));
	}

	if (!dialup())
	{
		if (m_progress)
			m_progress->end();

		m_port->close();

		return false;
	}

	/*
		* Wait 1s before probing modem. As meter has some delay.
		*/
	ZProtocol::msleep(1000);

	if (!probeModem())
	{
		if (m_progress)
			m_progress->end();

		m_port->close();

		setErrorString(tr("Transparent mode is enabled but modem still not responding"));
		return false;
	}

	if (m_progress)
		m_progress->end();

    return ZChannel::connect();
}

void ZChannelCSD::disconnect()
{
	m_port->close();
	ZChannel::disconnect();
}