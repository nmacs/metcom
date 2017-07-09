#include "zchanneldirectserial.h"
#include "zprotocol.h"
#include <QThread>
#include <QDebug>

ZChannelDirectSerial::ZChannelDirectSerial(QObject *parent) : ZChannel(parent)
{
    m_port = new QSerialPort(this);
	attach(m_port);
}

ZChannelDirectSerial::~ZChannelDirectSerial()
{
	disconnect();
}

bool ZChannelDirectSerial::connect()
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

	if (m_progress)
	{
		m_progress->start();
		m_progress->setProgress(-1, tr("Connecting..."));
	}

    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);
	m_port->setParity(QSerialPort::NoParity);
	m_port->setDataBits(QSerialPort::Data8);
	m_port->setDataTerminalReady(true);

    setBaudRate(9600);

	//QString stop = QString("STOP=%1\r").arg(password());
	//write(stop.toLatin1().constData(), stop.length(), defaultTimeout());
	ZProtocol::msleep(500);

	if (!probeModem())
	{
		m_port->close();
		if (m_progress)
			m_progress->end();
		setErrorString(tr("Fail to communicate with the Modem"));
		return false;
	}

	if (m_progress)
		m_progress->end();

    return ZChannel::connect();
}

void ZChannelDirectSerial::disconnect()
{
	if (!isConnected())
		return;

	//QString stop = QString("START=%1\r").arg(password());
	//write(stop.toLatin1().constData(), stop.length(), 500);
	ZProtocol::msleep(500);

    m_port->close();
	ZChannel::disconnect();
}

QIODevice* ZChannelDirectSerial::device()
{
    return m_port;
}

void ZChannelDirectSerial::setPortName(const QString &port)
{
    m_port->setPortName(port);
}

QString ZChannelDirectSerial::portName() const
{
    return m_port->portName();
}

void ZChannelDirectSerial::setBaudRate(int baud)
{
    m_port->setBaudRate(baud);
}

int ZChannelDirectSerial::baudRate() const
{
   return m_port->baudRate();
}

int ZChannelDirectSerial::defaultTimeout()
{
    return 1500;
}
