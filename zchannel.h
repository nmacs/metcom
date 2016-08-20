#ifndef ZCHANNEL_H
#define ZCHANNEL_H

#include <QObject>
#include <QIODevice>
#include "zcommlog.h"

class ZChannel : public QObject
{
    Q_OBJECT
public:
    explicit ZChannel(QObject *parent = 0);

    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual QIODevice* device() = 0;

    virtual int defaultTimeout() = 0;

    bool write(const char* data, qint64 length, int timeout);
    qint64 read(char* data, qint64 length, int timeout);

    void setCommLog(ZCommLog *log);

    QString const& errorString() const { return m_errorString; }

signals:

public slots:

protected:
    void setErrorString(const QString& error) { m_errorString = error; }
    void yield();

private:
    QString m_errorString;
    ZCommLog *m_log;
};

#endif // ZCHANNEL_H
