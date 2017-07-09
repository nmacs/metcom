#ifndef ZCHANNELOPTO_H
#define ZCHANNELOPTO_H

#include <QSerialPort>
#include "zchanneldirectserial.h"

class ZChannelOpto : public ZChannelDirectSerial
{
    Q_OBJECT
public:
	enum PortMode {
		mode_7E1,
		mode_8N1,
	};

    explicit ZChannelOpto(PortMode mode = mode_7E1, QObject *parent = 0);
	virtual ~ZChannelOpto();

    virtual bool connect();
	virtual void disconnect();

    virtual int defaultTimeout();
	virtual bool isLongConnect() const { return false; }

	void setMeterPassword(const QString &password) { m_meterPassword = password; }
	const QString& meterPassword() const { return m_meterPassword; }
	PortMode getMode() const { return m_mode; }

signals:

public slots:

private:
	bool enterTransparentMode();
	QString m_meterPassword;
	PortMode m_mode;
};

#endif // ZCHANNELOPTO_H
