#include "zchannelsocket.h"
#include "zprotocol.h"
#include <QHostAddress>

ZChannelSocket::ZChannelSocket(QObject *parent /*= 0*/) :
	ZChannel(parent)
{
	m_socket = new QTcpSocket(this);

	QObject::connect(m_socket, &QTcpSocket::connected, this, &ZChannelSocket::on_socket_connected);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &ZChannelSocket::on_socket_disconnected);

	attach(m_socket);
}

ZChannelSocket::~ZChannelSocket()
{
	disconnect();
	delete m_socket;
}

bool ZChannelSocket::connect()
{
	if (isConnected())
		return true;

	int timeout = defaultTimeout();
	QAbstractSocket::SocketState state;

	if (m_progress)
	{
		m_progress->start();
		m_progress->setProgress(-1, tr("Connecting..."));
	}

	m_connected = false;
	m_socket->connectToHost(QHostAddress(m_address), m_port);

	while (timeout > 0)
	{
		if (m_connected)
			break;

		state = m_socket->state();
		if (state != QAbstractSocket::HostLookupState && state != QAbstractSocket::ConnectingState)
			break;

		ZProtocol::msleep(30);
	}

	if (!m_connected)
	{
		setErrorString(m_socket->errorString());
		m_socket->abort();

		if (m_progress)
			m_progress->end();

		return false;
	}

	if (!probeModem())
	{
		if (m_progress)
			m_progress->end();

		m_socket->abort();

		setErrorString(tr("Modem is not responding"));
		return false;
	}

	if (m_progress)
		m_progress->end();

	return ZChannel::connect();
}

void ZChannelSocket::disconnect()
{
	m_socket->disconnectFromHost();
	ZChannel::disconnect();
}

void ZChannelSocket::on_socket_connected()
{
	m_connected = true;
}

void ZChannelSocket::on_socket_disconnected()
{
	m_disconnected = true;
}