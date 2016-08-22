#include "zprotocol.h"
#include <QCoreApplication>
#include <QThread>

ZProtocol::ZProtocol(ZChannel *channel, Progress *progress, QObject *parent) :
    QObject(parent),
    m_progress(progress)
{
    setChannel(channel);
}

void ZProtocol::handleErrorResponse(const QString& response)
{
    QRegExp rx("ERROR: (\\d*)");
    int pos = rx.indexIn(response);
    if (pos >= 0)
    {
        int code = rx.cap(1).toInt();
        switch (code)
        {
        case 0:
            setErrorString(tr("Invalid password"));
            break;
        case 1:
            setErrorString(tr("Flash write failed"));
            break;
        default:
            setErrorString(QString(tr("Unknown error code: %1").arg(code)));
            break;
        }
    }
    else
    {
        setErrorString(tr("Invalid response format"));
    }
}

ZChannel* ZProtocol::channel()
{
    return m_channel;
}

void ZProtocol::setChannel(ZChannel *channel)
{
    m_channel = channel;
    if (m_channel)
    {
        setTimeout(m_channel->defaultTimeout());
        setPassword(m_channel->password());
    }
}

void ZProtocol::setPassword(const QString &password)
{
    m_password = password;
}

void ZProtocol::setTimeout(int value)
{
    m_timeout = value;
}

void ZProtocol::msleep(int msec)
{
    while (msec > 0)
    {
        QCoreApplication::processEvents();
        QThread::msleep(20);
        msec -= 20;
    }
}

bool ZProtocol::connect()
{
    bool res;

    if (m_channel == 0)
    {
        return false;
    }

    res = m_channel->connect();
    if (!res)
    {
        setErrorString((m_channel->errorString()));
        return false;
    }

    return true;
}

void ZProtocol::disconnect()
{
    if (m_channel == 0)
    {
        return;
    }

    m_channel->disconnect();
}

bool ZProtocol::run()
{
    bool ret;

    if (m_progress)
    {
        m_progress->start();
    }

    ret = doRun();

    if (m_progress)
    {
        m_progress->end();
    }

    return ret;
}

bool ZProtocol::execute(const QString& command, const QByteArray& tail, bool noresponse)
{
    bool res;
    char buffer[1024];
    qint64 len;
    QString response;
    QByteArray request;

    request.append(command);
    request.append(tail);

    res = channel()->write(request.constData(), request.length(), m_timeout);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    if (noresponse)
    {
        return true;
    }

    len = channel()->read(buffer, sizeof(buffer), m_timeout);
    if (len < 0)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    if (len >= sizeof(buffer))
    {
        setErrorString(tr("Too long modem response"));
        return false;
    }
    buffer[len] = '\0';

    response = QString(buffer);
    if (response != "OK\r\n")
    {
        if (response.left(7) == "ERROR: ")
        {
            handleErrorResponse(response);
        }
        else
        {
            setErrorString(tr("Invalid response format"));
        }

        return false;
    }

    return true;
}

bool ZProtocol::readout(QStringList *lines, int maxlines)
{
    char buffer[1024];
    qint64 len;
    bool ok = false;

    while (maxlines > 0)
    {
        len = channel()->read(buffer, sizeof(buffer), m_timeout);

        if (len < 0)
        {
            setErrorString(channel()->errorString());
            return false;
        }
        else if (len == 0)
        {
            break;
        }
        else
        {
            if (len >= sizeof(buffer))
            {
                setErrorString(tr("Too long modem response"));
                return false;
            }
            buffer[len] = '\0';

            QString line = QString(buffer);
            if (line == "OK\r\n")
            {
                ok = true;
                break;
            }
            else if (line.left(7) == "ERROR: ")
            {
                handleErrorResponse(line);
                return false;
            }
            else
            {
                lines->append(line);
            }
        }
    }

    if (maxlines == 0)
    {
        setErrorString(tr("Loo many lines in modem response."));
        return false;
    }

    if (!ok)
    {
        setErrorString(tr("No OK from modem. Response truncated."));
        return false;
    }

    return true;
}

bool ZProtocol::cancelRequest() const
{
   return m_progress != 0 ? m_progress->cancelRequest() : false;
}

void ZProtocol::reportProgress(double progress, QString const& message)
{
    if (m_progress)
    {
        m_progress->setProgress(progress, message);
    }
}
