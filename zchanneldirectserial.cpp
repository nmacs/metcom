#include "zchanneldirectserial.h"

ZChannelDirectSerial::ZChannelDirectSerial(QObject *parent) : ZChannel(parent)
{
    m_port = new QSerialPort(this);

    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);

    setBaudRate(QSerialPort::Baud115200);
}

bool ZChannelDirectSerial::connect()
{
    bool res;

    res = m_port->open(QIODevice::ReadWrite);
    if (!res)
    {
        setErrorString(m_port->errorString());
        return false;
    }

    return true;
}

void ZChannelDirectSerial::disconnect()
{
    m_port->close();
}

QIODevice* ZChannelDirectSerial::device()
{
    return m_port;
}

void ZChannelDirectSerial::setPortName(const QString &port)
{
    m_port->setPortName(port);
}

void ZChannelDirectSerial::setBaudRate(QSerialPort::BaudRate baud)
{
    m_port->setBaudRate(baud);
}

int ZChannelDirectSerial::defaultTimeout()
{
    return 10000;
}
