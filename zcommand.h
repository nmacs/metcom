#ifndef ZCOMMAND_H
#define ZCOMMAND_H

#include "zprotocol.h"

class ZCommand : public ZProtocol
{
public:
    ZCommand(QString const& command, QString const& title, ZChannel *channel = 0, Progress *progress = 0, QObject *parent = 0);

protected:
    virtual bool doRun();

private:
    QString m_command;
    QString m_title;
};

#endif // ZCOMMAND_H
