#include "zchanneldirectserial.h"
#include <QThread>
#include <QDebug>

ZChannelDirectSerial::ZChannelDirectSerial(QObject *parent) : ZChannel(parent)
{
    m_optical = false;
    m_port = new QSerialPort(this);
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

    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    if (m_optical)
    {
        char input_buffer[128];

        m_port->setParity(QSerialPort::EvenParity);
        m_port->setDataBits(QSerialPort::Data7);
        setBaudRate(300);

        static const char start[] = {
            0x2F, 0x3F, 0x21, 0x0D, 0x0A
        };

        write(start, sizeof(start), 500);
        qint64 r = read(input_buffer, sizeof(input_buffer), 1000);
        if (r < 0)
        {
            m_port->close();
            setErrorString(tr("Fail to communicate with meter"));
            return false;
        }

        static const char speed_change[] = {
            0x06, 0x30, 0x35, 0x31, 0x0D, 0x0A
        };

        write(speed_change, sizeof(speed_change), 1000);
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
            m_port->close();
            return false;
        }
    }
    else
    {
        setBaudRate(115200);
    }

    m_port->setParity(QSerialPort::NoParity);
    m_port->setDataBits(QSerialPort::Data8);

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

QString ZChannelDirectSerial::portName() const
{
    return m_port->portName();
}

void ZChannelDirectSerial::setMeterPassword(const QString &password)
{
    m_meterPassword = password;
}

void ZChannelDirectSerial::setBaudRate(int baud)
{
    m_port->setBaudRate(baud);
}

int ZChannelDirectSerial::baudRate() const
{
   return m_port->baudRate();
}

void ZChannelDirectSerial::setOpticalMode(bool enable)
{
    m_optical = enable;
}

bool ZChannelDirectSerial::opticalMode() const
{
    return m_optical;
}

int ZChannelDirectSerial::defaultTimeout()
{
    return 10000;
}
