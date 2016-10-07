#ifndef ZCHANNELSOCKET_H
#define ZCHANNELSOCKET_H

#include "zchannel.h"
#include <QTcpSocket>

class ZChannelSocket : public ZChannel
{
	Q_OBJECT
public:
	ZChannelSocket(QObject *parent = 0);
	~ZChannelSocket();

	virtual bool connect();
	virtual void disconnect();

	virtual QIODevice* device() { return m_socket; }

	virtual bool isMediaConnected() { return m_connected; }
	virtual bool isLongConnect() const { return true; }
	virtual int defaultTimeout() { return 10000; }

	QString const& address() const { return m_address; }
	void setAddress(QString const& address) { m_address = address; }

	quint16 port() const { return m_port; }
	void setPort(quint16 port) { m_port = port; }

private slots:
	void on_socket_connected();
	void on_socket_disconnected();

private:
	QTcpSocket *m_socket;
	QString m_address;
	quint16 m_port;
	bool m_connected;
	bool m_disconnected;
};

#endif // ZCHANNELSOCKET_H