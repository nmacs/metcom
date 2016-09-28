#ifndef ZPROTOCOL_H
#define ZPROTOCOL_H

#include <QObject>
#include <QIODevice>
#include <QProgressBar>
#include "zchannel.h"
#include "progress.h"

class ZProtocol : public QObject
{
    Q_OBJECT
public:
    explicit ZProtocol(ZChannel *channel = 0, Progress *progress = 0, QObject *parent = 0);

    ZChannel *channel();
    void setChannel(ZChannel *channel);
    void setPassword(const QString &password);
    void setCommunicationTimeout(int value);
    void setProgress(Progress *progress);

    static void msleep(int msec);

    bool run();

    QString const& errorString() const { return m_errorString; }

signals:

public slots:

protected:
    virtual bool doRun() = 0;

    const QString& password() const { return m_password; }
    void setErrorString(const QString& error) { m_errorString = error; }
    void reportProgress(double progress, QString const& message = QString());

	bool post(const QByteArray& commdand);
	bool post(const QString& command);
	bool execute(const QByteArray& command, int timeout = 500);
    bool execute(const QString& command, int timeout = 500);
    bool readout(QStringList *lines, int maxlines, int timeout = 500);
    bool cancelRequest() const;

private:
    void handleErrorResponse(const QString& response);

    ZChannel *m_channel;
    Progress *m_progress;
    QString m_password;
    QString m_errorString;
    int m_communicationTimeout;
};

#endif // ZPROTOCOL_H
