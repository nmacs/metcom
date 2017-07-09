#include "zpasswordchange.h"

#define CONFIG_METCOM_ETHERNET

ZPasswordChange::ZPasswordChange(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent)
{
}

bool ZPasswordChange::doRun()
{
    int res;
    QString command;

    reportProgress(-1, tr("Changing Password..."));

#ifndef CONFIG_METCOM_ETHERNET
    command = QString("PSW=%1;%2\r").arg(password(), m_newPassword);
    res = execute(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }
#else
	command = QString("PUT=%1;PASSW=%2\r").arg(password(), m_newPassword);
	res = execute(command);
	if (!res)
	{
		setErrorString(channel()->errorString());
		return false;
	}

	command = QString("SAVE=%1\r").arg(password());
	res = execute(command);
	if (!res)
	{
		setErrorString(channel()->errorString());
		return false;
	}
#endif

    return true;
}

void ZPasswordChange::setNewPassword(QString const& password)
{
    m_newPassword = password;
}
