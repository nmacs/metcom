#ifndef ZPROTOCOL_H
#define ZPROTOCOL_H

#include <QObject>
#include <QIODevice>
#include <QProgressBar>
#include "zchannel.h"

class ZProtocol : public QObject
{
    Q_OBJECT
public:
    explicit ZProtocol(ZChannel *channel = 0, QObject *parent = 0);

    ZChannel *channel();
    void setChannel(ZChannel *channel);
    void setPassword(const QString &password);
    void setTimeout(int value);
    void setProgress(QProgressBar *progress);

    static void msleep(int msec);
    virtual bool run() = 0;

    virtual bool connect();
    virtual void disconnect();

    QString const& errorString() const { return m_errorString; }

signals:

public slots:

protected:
    const QString& password() const { return m_password; }
    void setErrorString(const QString& error) { m_errorString = error; }
    QProgressBar* progress() { return m_progress; }

    bool execute(const QString& command, const QByteArray& tail = QByteArray(), bool noresponse = false);
    bool readout(QStringList *lines, int maxlines);

private:
    void handleErrorResponse(const QString& response);

    ZChannel *m_channel;
    QProgressBar *m_progress;
    QString m_password;
    QString m_errorString;
    int m_timeout;
};

#endif // ZPROTOCOL_H
