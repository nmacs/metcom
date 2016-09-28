#include "zreadsettings.h"
#include <QDebug>

ZReadSettings::ZReadSettings(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent)
{
}

bool ZReadSettings::doRun()
{
    bool res;
    QString command;
    QStringList lines;

    reportProgress(-1, tr("Reading settings from modem..."));

    command = QString("GET=%1\r").arg(password());
    res = post(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    res = readout(&lines, 1024, 2000);
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

    return true;
}
