#ifndef ZCHANNELDIRECTSERIAL_H
#define ZCHANNELDIRECTSERIAL_H

#include <QSerialPort>
#include "zchannel.h"

class ZChannelDirectSerial : public ZChannel
{
    Q_OBJECT
public:
    explicit ZChannelDirectSerial(QObject *parent = 0);

    virtual bool connect();
    virtual void disconnect();
    virtual QIODevice* device();

    void setPortName(const QString &port);
    void setBaudRate(QSerialPort::BaudRate baud);

    virtual int defaultTimeout();

signals:

public slots:

private:
    QSerialPort *m_port;
};

#endif // ZCHANNELDIRECTSERIAL_H
