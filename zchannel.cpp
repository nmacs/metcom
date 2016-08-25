#include "zchannel.h"
#include <QCoreApplication>
#include <QDebug>

#define GUI_POLLING_INTERVAL_MS 30

ZChannel::ZChannel(QObject *parent) : QObject(parent),
    m_progress(0),
    m_log(0)
{
}

bool ZChannel::write(const char* data, qint64 length, int timeout)
{
    while (length > 0)
    {
        if (m_log)
        {
            m_log->log(QByteArray(data, length), ZCommLog::LOG_OUTPUT);
        }

        qint64 ret = device()->write(data, length);
        if (ret < 0)
        {
            setErrorString(device()->errorString());
            return false;
        }

        if (m_progress != 0 && m_progress->cancelRequest())
        {
           setErrorString(tr("Operation cancelled"));
           return false;
        }

        if (ret > 0)
        {
            length -= ret;
            data += length;
        }

        while (timeout > 0)
        {
            if (m_progress != 0 && m_progress->cancelRequest())
            {
               setErrorString(tr("Operation cancelled"));
               return false;
            }

            yield();

            if (device()->waitForBytesWritten(GUI_POLLING_INTERVAL_MS))
                break;

            timeout -= GUI_POLLING_INTERVAL_MS;
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
    qint64 ret;
    qint64 bytesRead = 0;

    while (maxLength > 0)
    {
        ret = device()->read(&ch, 1);
        if (ret < 0)
        {
            setErrorString(device()->errorString());
            return -1;
        }

        if (m_progress != 0 && m_progress->cancelRequest())
        {
           setErrorString(tr("Operation cancelled"));
           return -1;
        }

        if (ret > 0)
        {
new_byte:
            data[bytesRead] = ch;
            qDebug() << "byte " << ch;

            bytesRead += 1;
            maxLength -= 1;

            if (ch == '\n')
            {
                break;
            }
        }
        else
        {
            while (timeout > 0)
            {
                if (m_progress != 0 && m_progress->cancelRequest())
                {
                   setErrorString(tr("Operation cancelled"));
                   return -1;
                }

                yield();

                if (device()->waitForReadyRead(GUI_POLLING_INTERVAL_MS))
                    break;

                timeout -= GUI_POLLING_INTERVAL_MS;

                ret = device()->read(&ch, 1);
                if (ret > 0)
                {
                    goto new_byte;
                }
            }

            if (timeout <= 0)
            {
                setErrorString(tr("Channel read timeout."));
                return -1;
            }
        }
    }

    if (m_log)
    {
        m_log->log(QByteArray(data, bytesRead), ZCommLog::LOG_INPUT);
    }

    return bytesRead;
}

void ZChannel::yield()
{
    QCoreApplication::processEvents();
}

void ZChannel::setProgress(Progress *progress)
{
    m_progress = progress;
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
