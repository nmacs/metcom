#ifndef ZCHANNELCSD_H
#define ZCHANNELCSD_H

#include <QSerialPort>
#include "zchanneldirectserial.h"

class ZChannelCSD : public ZChannelDirectSerial
{
    Q_OBJECT
public:
    explicit ZChannelCSD(QObject *parent = 0);
	virtual ~ZChannelCSD();

    virtual bool connect();
	virtual void disconnect();

	virtual int defaultTimeout() { return 10000; }
	virtual bool isLongConnect() const { return true; }

	void setPhoneNumber(const QString &phone) { m_phone = phone; }
	const QString& phoneNumbaer() const { return m_phone; }

signals:

public slots:

private:
	bool dialup();
	QString m_phone;
};

#endif // ZCHANNELOPTO_H
