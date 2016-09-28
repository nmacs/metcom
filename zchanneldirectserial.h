#ifndef ZCHANNELDIRECTSERIAL_H
#define ZCHANNELDIRECTSERIAL_H

#include <QSerialPort>
#include "zchannel.h"

class ZChannelDirectSerial : public ZChannel
{
    Q_OBJECT
public:
    explicit ZChannelDirectSerial(QObject *parent = 0);
	virtual ~ZChannelDirectSerial();

    virtual bool connect();
    virtual void disconnect();
    virtual QIODevice* device();

	virtual bool isLongConnect() const { return false; }

    void setPortName(const QString &port);
    QString portName() const;

    void setBaudRate(int baud);
    int baudRate() const;

    virtual int defaultTimeout();

signals:

public slots:

protected:
	QSerialPort *m_port;
};

#endif // ZCHANNELDIRECTSERIAL_H
