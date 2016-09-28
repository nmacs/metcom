#ifndef ZCHANNELOPTO_H
#define ZCHANNELOPTO_H

#include <QSerialPort>
#include "zchanneldirectserial.h"

class ZChannelOpto : public ZChannelDirectSerial
{
    Q_OBJECT
public:
    explicit ZChannelOpto(QObject *parent = 0);
	virtual ~ZChannelOpto();

    virtual bool connect();
	virtual void disconnect();

    virtual int defaultTimeout();
	virtual bool isLongConnect() const { return false; }

	void setMeterPassword(const QString &password) { m_meterPassword = password; }
	const QString& meterPassword() const { return m_meterPassword; }

signals:

public slots:

private:
	bool enterTransparentMode();
	QString m_meterPassword;
};

#endif // ZCHANNELOPTO_H
