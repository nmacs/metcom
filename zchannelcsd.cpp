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
	qint64 r;
	int i;
	char input_buffer[128];

	QString at = QString("AT\r");
	write(at, 500);

	for (i = 0; i < 5; i++)
	{
		r = read(input_buffer, sizeof(input_buffer), 1000);
		if (r < 0)
		{
			setErrorString(QString(tr("No response from local modem: %1")).arg(errorString()));
			return false;
		}

		if (r >= 2 && memcmp(input_buffer, "OK\r\n", 4) == 0)
		{
			break;
		}
	}
	if (i >= 5)
	{
		setErrorString(QString(tr("No response from local modem: %1")).arg(errorString()));
		return false;
	}


	QString atd = QString("ATD%1\r").arg(m_phone);
	write(atd, 500);

	for (i = 0; i < 5; i++)
	{
		r = read(input_buffer, sizeof(input_buffer), 60000);
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

	setErrorString(QString(tr("No response from local modem: %1")).arg(errorString()));
	return false;
}

void ZChannelCSD::hookup()
{
	char input_buffer[128];

	ZProtocol::msleep(1000);
	write(QString("+++"), 500);

	for (int i = 0; i < 5; i++)
	{
		qint64 r = read(input_buffer, sizeof(input_buffer), 2000);
		if (r < 0)
		{
			return;
		}

		if (r >= 2 && memcmp(input_buffer, "OK\r\n", 4) == 0)
			break;
	}

	write(QString("ATH0\r"), 500);

	for (int i = 0; i < 5; i++)
	{
		qint64 r = read(input_buffer, sizeof(input_buffer), 2000);
		if (r < 0)
		{
			return;
		}

		if (r >= 2 && memcmp(input_buffer, "OK\r\n", 4) == 0)
			break;
	}
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

		hookup();
		m_port->close();

		setErrorString(tr("Remote modem is not responding"));
		return false;
	}

	if (m_progress)
		m_progress->end();

    return ZChannel::connect();
}

void ZChannelCSD::disconnect()
{
	if (!isConnected())
		return;

	if (m_progress)
	{
		m_progress->start();
		m_progress->setProgress(-1, tr("Disconnecting..."));
	}

	hookup();

	m_port->close();
	ZChannel::disconnect();

	if (m_progress)
		m_progress->end();
}

void ZChannelCSD::readyRead()
{
	QByteArray bytes = device()->peek(128 * 1024);
	QString str = QString(bytes);

	int index = str.indexOf("NO CARRIER\r\n", 0, Qt::CaseInsensitive);
	if (index >= 0)
	{
		m_port->close();
		ZChannel::disconnect();
	}
}