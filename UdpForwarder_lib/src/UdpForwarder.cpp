#include "UdpForwarder.h"
#include <QNetworkDatagram>
UdpForwarder::UdpForwarder(const QString &remoteAddr, qint64 remotePort, const QString &localipv4Addr,
                           const QString &localipv6Addr, qint64 localPort, QObject *parent)
	: QObject(parent)
	, remoteipv6Addr(remoteAddr)
	, localipv4Addr(localipv4Addr)
	, localipv6Addr(localipv6Addr)
	, remoteipv6Port(remotePort)
	, localPort(localPort)
{
	/// 初始化IPV6Socket
	ipv6socket = new QUdpSocket(this);
	/// 绑定本地IPV6Socket
	if (!ipv6socket->bind(QHostAddress(localipv6Addr), remotePort))
	{
		throw std::runtime_error("IPV6绑定失败!");
		return;
	}
	/// 初始化IPV4Socket
	ipv4socket = new QUdpSocket(this);
	if (!ipv4socket->bind(QHostAddress(localipv4Addr), localPort))
	{
		throw std::runtime_error("IPV4绑定失败!");
		return;
	}

	/// 连接Socket接受信号
	connect(ipv6socket, &QUdpSocket::readyRead, this, &UdpForwarder::ipv6Recv);
	connect(ipv4socket, &QUdpSocket::readyRead, this, &UdpForwarder::ipv4Recv);

	/// 连接Socket发送信号
	connect(this, &UdpForwarder::Udp6To4, this, &UdpForwarder::ipv4Send);
	connect(this, &UdpForwarder::Udp4To6, this, &UdpForwarder::ipv6Send);
}

void UdpForwarder::ipv6Recv()
{
	const auto datagram = ipv6socket->receiveDatagram();
	emit Udp6To4(datagram.data());
}

void UdpForwarder::ipv6Send(const QByteArray &msg) const
{
	ipv6socket->writeDatagram(msg, QHostAddress(remoteipv6Addr), remoteipv6Port);
}

void UdpForwarder::ipv4Send(const QByteArray &msg) const
{
	ipv4socket->writeDatagram(msg, QHostAddress(remoteipv4Addr), remoteipv4Port);
}

void UdpForwarder::ipv4Recv()
{
	const auto datagram = ipv4socket->receiveDatagram();
	/// 第一次获取消息时，更新ipv4地址和端口
	if (remoteipv4Addr.isEmpty())
	{
		remoteipv4Addr = datagram.senderAddress().toString();
		remoteipv4Port = datagram.senderPort();
	}
	emit Udp4To6(datagram.data());
}
