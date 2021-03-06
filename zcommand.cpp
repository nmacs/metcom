#include "zcommand.h"

ZCommand::ZCommand(const QString &command, const QString &title, ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent),
	m_haveResponse(false),
    m_command(command),
    m_title(title),
	m_timeout(1000)
{
}

bool ZCommand::doRun()
{
    bool res;

    reportProgress(-1, m_title);

	if (!m_haveResponse)
	{
		res = execute(m_command.arg(password()), m_timeout);
		if (!res)
		{
			setErrorString(channel()->errorString());
			return false;
		}
	}
	else
	{
		res = post(m_command.arg(password()));
		if (!res)
		{
			setErrorString(channel()->errorString());
			return false;
		}

		res = readout(&m_response, 128, m_timeout);
		if (!res)
		{
			setErrorString(channel()->errorString());
			return false;
		}
	}

    return true;
}
