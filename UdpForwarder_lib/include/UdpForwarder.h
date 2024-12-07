#ifndef UDPFORWARDER_H
#define UDPFORWARDER_H

#ifdef _MSC_VER
#define EXPORT_SYMBOL __declspec(dllexport)
#else
	#define EXPORT_SYMBOL __attribute__((visibility("default")))
#endif

#include <QObject>
#include <QUdpSocket>

class EXPORT_SYMBOL UdpForwarder : public QObject
{
	Q_OBJECT

public:
	UdpForwarder(const QString &remoteAddr, qint64 remotePort, const QString &localipv4Addr,
	             const QString &localipv6Addr, qint64 localPort, QObject *parent = nullptr);

private :
	/// 接受IPV6
	void ipv6Recv();

	/// 发送IPV6
	void ipv6Send(const QByteArray &msg) const;

	/// 发送IPV4
	void ipv4Send(const QByteArray &msg) const;

	/// 接受IPV4
	void ipv4Recv();

	QUdpSocket *ipv6socket = nullptr;
	QUdpSocket *ipv4socket = nullptr;
	QString remoteipv6Addr{};
	QString remoteipv4Addr{};
	QString localipv4Addr{};
	QString localipv6Addr{};
	qint64 remoteipv6Port = -1;
	qint64 remoteipv4Port = -1;
	qint64 localPort = -1;
signals:
	/// 将IPV6发给IPV4
	void Udp6To4(QByteArray msg);

	/// 将IPV4发给IPV6
	void Udp4To6(QByteArray msg);
};


#endif //UDPFORWARDER_H
