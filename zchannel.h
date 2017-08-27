#ifndef ZCHANNEL_H
#define ZCHANNEL_H

#include <QObject>
#include <QIODevice>
#include <QTime>
#include "progress.h"
#include "zcommlog.h"

class ZChannel : public QObject
{
    Q_OBJECT
public:
    explicit ZChannel(QObject *parent = 0);

    virtual bool connect();
    virtual void disconnect();
	bool isConnected() const { return m_isConnected; }
	virtual bool isMediaConnected() { return device()->isOpen(); }

    virtual QIODevice* device() = 0;

	virtual bool isLongConnect() const = 0;
    virtual int defaultTimeout() = 0;

    void setProgress(Progress *progress);
    void setCommLog(ZCommLog *log);

    void setPassword(QString const& password);
    QString const& password() const;

	bool write(const QString& data, int timeout);
    bool write(const char* data, qint64 length, int timeout);
    qint64 read(char* data, qint64 length, int timeout);

    QString const& errorString() const { return m_errorString; }
	int connectionTime() const;

signals:
	void connected(bool connected);

private slots:
	void on_readyRead();
	void on_bytesWritten(qint64 bytes);

protected:
	virtual void readyRead() {}
	virtual void bytesWritten(qint64 bytes) { (void)bytes;  }

	void attach(QIODevice *device);
    void setErrorString(const QString& error) { m_errorString = error; }
    void yield();
	bool probeModem(int retries = 1);

protected:
	Progress *m_progress;

private:
    QString m_password;
    QString m_errorString;
    ZCommLog *m_log;
	bool m_isConnected;
	QTime m_connectedTime;
	quint64 m_bytesWriten;
	bool m_readyRead;
};

#endif // ZCHANNEL_H
