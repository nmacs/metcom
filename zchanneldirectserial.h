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
    QString portName() const;

    void setMeterPassword(const QString &password);

    void setBaudRate(int baud);
    int baudRate() const;

    void setOpticalMode(bool enable);
    bool opticalMode() const;

    virtual int defaultTimeout();

signals:

public slots:

private:
    QSerialPort *m_port;
    QString m_meterPassword;
    bool m_optical;
};

#endif // ZCHANNELDIRECTSERIAL_H
