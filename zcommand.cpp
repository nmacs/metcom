#include "zcommand.h"

ZCommand::ZCommand(const QString &command, const QString &title, ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent),
    m_command(command),
    m_title(title)
{
}

bool ZCommand::doRun()
{
    int res;

    reportProgress(-1, m_title);

    res = execute(m_command.arg(password()));
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    return true;
}
