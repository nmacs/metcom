#include "zchannel.h"
#include "zprotocol.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#define GUI_POLLING_INTERVAL_MS 30

ZChannel::ZChannel(QObject *parent) : QObject(parent),
    m_progress(0),
    m_log(0),
	m_isConnected(false)
{
}

bool ZChannel::connect()
{
	m_connectedTime = QTime::currentTime();
	m_isConnected = true;
	emit connected(true);
	return true;
}

void ZChannel::disconnect()
{
	m_isConnected = false;
	emit connected(false);
}

int ZChannel::connectionTime() const
{
	if (!m_isConnected)
		return 0;

	return m_connectedTime.secsTo(QTime::currentTime());
}

bool ZChannel::write(const QString& data, int timeout)
{
	return write(data.toLatin1().constData(), data.length(), timeout);
}

bool ZChannel::write(const char* data, qint64 length, int timeout)
{
    while (length > 0)
    {
        if (m_log)
        {
            m_log->log(QByteArray(data, length), ZCommLog::LOG_OUTPUT);
        }

		if (!isMediaConnected())
		{
			setErrorString(tr("Channel closed unexpectedly"));
			return false;
		}
		else if (m_progress != 0 && m_progress->cancelRequest())
		{
			setErrorString(tr("Operation cancelled"));
			return false;
		}

		m_bytesWriten = 0;
        qint64 ret = device()->write(data, length);
        if (ret <= 0)
        {
            setErrorString(device()->errorString());
            return false;
        }

        length -= ret;
        data += length;

        while (timeout > 0)
        {
            if (m_progress != 0 && m_progress->cancelRequest())
            {
               setErrorString(tr("Operation cancelled"));
               return false;
            }

			if (m_bytesWriten > 0)
			{
				ret -= m_bytesWriten;
				m_bytesWriten = 0;
			}

			if (ret == 0)
				break;

			ZProtocol::msleep(20);
			timeout -= 20;
        }

        if (timeout <= 0)
        {
            setErrorString(tr("Channel write timeout."));
            return false;
        }
    }

    return true;
}

qint64 ZChannel::read(char *data, qint64 maxLength, int timeout)
{
    char ch;
    qint64 ret = 0;
    qint64 bytesRead = 0;
	int waittime = 0;

    while (maxLength > 0)
    {
		if (m_progress != 0 && m_progress->cancelRequest())
		{
			setErrorString(tr("Operation cancelled"));
			ret = -1;
			goto out;
		}

        ret = device()->read(&ch, 1);
        if (ret < 0)
        {
            setErrorString(device()->errorString());
            ret = -1;
			goto out;
        }

        if (ret > 0)
        {
			waittime = 0;
			data[bytesRead] = ch;
			qDebug() << "byte " << (unsigned)ch;

			bytesRead += 1;
			maxLength -= 1;

			if (ch == '\n')
			{
				if (memcmp(data, "NO CARRIER", 10) == 0)
				{
					disconnect();
					ret = -1;
					goto out;
				}
				break;
			}
        }
        else
        {
			if (!isMediaConnected())
			{
				setErrorString(tr("Channel closed unexpectedly"));
				ret = -1;
				goto out;
			}
			
			m_readyRead = false;
            while (waittime <= timeout)
            {
                if (m_progress != 0 && m_progress->cancelRequest())
                {
                   setErrorString(tr("Operation cancelled"));
				   ret = -1;
				   goto out;
                }

				if (m_readyRead)
					break;

				ZProtocol::msleep(GUI_POLLING_INTERVAL_MS);
                waittime += GUI_POLLING_INTERVAL_MS;
            }

            if (waittime >= timeout)
            {
                setErrorString(tr("Channel read timeout."));
				ret = -1;
				goto out;
            }
        }
    }

	ret = bytesRead;

out:
    if (m_log && bytesRead > 0)
    {
        m_log->log(QByteArray(data, bytesRead), ZCommLog::LOG_INPUT);
    }

    return bytesRead;
}

void ZChannel::attach(QIODevice *device)
{
	QObject::connect(device, &QIODevice::bytesWritten, this, &ZChannel::on_bytesWritten);
	QObject::connect(device, &QIODevice::readyRead,    this, &ZChannel::on_readyRead);
}

void ZChannel::on_readyRead()
{
	m_readyRead = true;
	readyRead();
}

void ZChannel::on_bytesWritten(qint64 bytes)
{
	m_bytesWriten = bytes;
	bytesWritten(bytes);
}

void ZChannel::setProgress(Progress *progress)
{
	m_progress = progress;
}

bool ZChannel::probeModem(int retries /*= 1*/)
{
	char buffer[1024];
	qint64 len;

	while (1)
	{
		retries--;

		QString command = QString("WRX=%1\r").arg(password());

		if (!write(command.toLatin1().constData(), command.length(), defaultTimeout()))
			goto error;

		len = read(buffer, sizeof(buffer), defaultTimeout());
		if (len != 4)
			goto error;

		if (memcmp(buffer, "OK\r\n", 4) != 0)
			goto error;

		return true;

	error:
		if (retries > 0)
			ZProtocol::msleep(500);
		else
			return false;
	} 

	return false;
}

void ZChannel::yield()
{
    QCoreApplication::processEvents();
}

void ZChannel::setCommLog(ZCommLog *log)
{
    m_log = log;
}

void ZChannel::setPassword(QString const& password)
{
    m_password = password;
}

QString const& ZChannel::password() const
{
    return m_password;
}
