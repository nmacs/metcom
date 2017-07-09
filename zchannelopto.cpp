#include "zchannelopto.h"
#include <QThread>
#include <QDebug>

#include "zprotocol.h"

ZChannelOpto::ZChannelOpto(PortMode mode /*= mode_7E1*/, QObject *parent) : ZChannelDirectSerial(parent), m_mode(mode)
{
}

ZChannelOpto::~ZChannelOpto()
{
	disconnect();
}

bool ZChannelOpto::enterTransparentMode()
{
	char input_buffer[128];

	if (m_mode == mode_7E1)
	{
		m_port->setParity(QSerialPort::EvenParity);
		m_port->setDataBits(QSerialPort::Data7);
	}
	else
	{
		m_port->setParity(QSerialPort::NoParity);
		m_port->setDataBits(QSerialPort::Data8);
	}
	setBaudRate(300);

	static const char start[] = {
		0x2F, 0x3F, 0x21, 0x0D, 0x0A
	};

	write(start, sizeof(start), 500);
	qint64 r = read(input_buffer, sizeof(input_buffer), 1500);
	if (r < 0)
		return false;

	static const char speed_change[] = {
		0x06, 0x30, 0x35, 0x31, 0x0D, 0x0A
	};

	write(speed_change, sizeof(speed_change), 1500);
	QThread::usleep(220000);
	m_port->setBaudRate(9600);
	read(input_buffer, 16, 500);

	char password[] = {
		0x01, 0x50, 0x31, 0x02, 0x28,
		0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
		0x29, 0x03, 0x61
	};

	int password_len = m_meterPassword.length();
	if (password_len > 8)
	{
		password_len = 8;
	}

	for (int i = 0; i < password_len; i++)
	{
		password[i + 5] = m_meterPassword.at(i).toLatin1();
	}

	char sum = 0;
	for (size_t i = 0; i < sizeof(password) - 2; i++)
	{
		sum ^= password[i + 1];
	}
	password[sizeof(password) - 1] = sum;

	write(password, sizeof(password), 1000);
	read(input_buffer, 1, 5000);

	static const char transparent[] = {
		0x01, 0x57, 0x31, 0x02,
		0x53, 0x30, 0x4E, 0x28,
		0x30, 0x41, 0x35, 0x30,
		0x29, 0x03, 0x3F
	};

	write(transparent, sizeof(transparent), 500);
	r = read(input_buffer, 5, 1000);
	if (r != 5)
	{
		setErrorString(tr("Unable to activate transparent mode"));
		return false;
	}

	return true;
}

bool ZChannelOpto::connect()
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

    m_port->setStopBits(QSerialPort::OneStop);
	m_port->setFlowControl(QSerialPort::NoFlowControl);
	m_port->setParity(QSerialPort::NoParity);
	m_port->setDataBits(QSerialPort::Data8);
	m_port->setBaudRate(9600);

	if (m_progress)
	{
		m_progress->start();
		m_progress->setProgress(-1, tr("Connecting..."));
	}

	if (probeModem())
	{
		if (m_progress)
			m_progress->end();
		return ZChannel::connect();
	}

	if (!enterTransparentMode())
	{
		if (m_progress)
			m_progress->end();
		m_port->close();
		return false;
	}

	m_port->setParity(QSerialPort::NoParity);
	m_port->setDataBits(QSerialPort::Data8);

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

void ZChannelOpto::disconnect()
{
	m_port->close();
	ZChannel::disconnect();
}

int ZChannelOpto::defaultTimeout()
{
    return 3000;
}
