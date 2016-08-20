#include "zchannel.h"
#include <QCoreApplication>

#define GUI_POLLING_INTERVAL_MS 30

ZChannel::ZChannel(QObject *parent) : QObject(parent)
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

        if (ret > 0)
        {
            length -= ret;
            data += length;
        }

        while (timeout > 0)
        {
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

        if (ret > 0)
        {
            data[bytesRead] = ch;

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
                yield();

                if (device()->waitForReadyRead(GUI_POLLING_INTERVAL_MS))
                    break;

                timeout -= GUI_POLLING_INTERVAL_MS;
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

void ZChannel::setCommLog(ZCommLog *log)
{
    m_log = log;
}

void ZChannel::yield()
{
    QCoreApplication::processEvents();
}
