#include "zreadsettings.h"
#include <QDebug>

ZReadSettings::ZReadSettings(ZChannel *channel, QObject *parent) :
    ZProtocol(channel, parent)
{
}

bool ZReadSettings::run()
{
    bool res;
    QString command;
    QStringList lines;

    command = QString("STOP=%1\r").arg(password());
    res = execute(command, QByteArray(), true);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    msleep(500);

    command = QString("GET=%1\r").arg(password());
    res = execute(command, QByteArray(), true);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    res = readout(&lines, 1024);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    m_settings.clear();

    QStringList::const_iterator iter;
    for (iter = lines.cbegin(); iter != lines.cend(); ++iter)
    {
        QRegExp rx("(.*)=(.*)\r\n");
        QString line = *iter;
        int pos = rx.indexIn(line);
        if (pos < 0)
        {
            setErrorString(tr("Invalid settings format"));
            return false;
        }

        m_settings.setValue(rx.cap(1), rx.cap(2));
    }

    command = QString("START=%1\r").arg(password());
    (void)execute(command, QByteArray(), true);
    msleep(500);

    return true;
}
