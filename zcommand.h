#ifndef ZCOMMAND_H
#define ZCOMMAND_H

#include "zprotocol.h"

class ZCommand : public ZProtocol
{
public:
    ZCommand(QString const& command, QString const& title, ZChannel *channel = 0, Progress *progress = 0, QObject *parent = 0);

	void setHaveResponse(bool value) { m_haveResponse = value; }
	void setTimeout(int value) { m_timeout = value; }
	QStringList const& response() const { return m_response; }

protected:
    virtual bool doRun();

private:
	bool m_haveResponse;
	QStringList m_response;
    QString m_command;
    QString m_title;
	int m_timeout;
};

#endif // ZCOMMAND_H
