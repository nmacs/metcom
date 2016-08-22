#include "zpasswordchange.h"

ZPasswordChange::ZPasswordChange(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent)
{
}

bool ZPasswordChange::doRun()
{
    int res;
    QString command;

    command = QString("PSW=%1;%2\r").arg(password(), m_newPassword);
    res = execute(command, QByteArray(), false);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    return true;
}

void ZPasswordChange::setNewPassword(QString const& password)
{
    m_newPassword = password;
}
