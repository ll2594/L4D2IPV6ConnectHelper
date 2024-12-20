#include <iostream>
#include <QCoreApplication>
#include <QHostInfo>
#include <QNetworkInterface>

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: socatCmdGenerator <serverDomain> <serverIPV6Port> <serverIPV4Port>" << std::endl;
		return -1;
	}
	QCoreApplication a(argc,argv);
	QString serverDomain = argv[1];
	QString serverIPV6Port = argv[2];
	QString serverIPV4Port = argv[3];
	QString serverIPV6;

	QHostInfo ipv6Info = QHostInfo::fromName(serverDomain);
	QList ipv6addrs = ipv6Info.addresses();
	for (const QHostAddress &addr: ipv6addrs)
	{
		if (addr.protocol() == QAbstractSocket::IPv6Protocol)
		{
			serverIPV6 = addr.toString();
		}
	}
	if (serverIPV6.isEmpty())
	{
		std::cerr << "cant find the IPV6 address for the domain！" << std::endl;;
		return -1;
	}

	/// windows下正常,linux只能获取到127.0.0.1，换成下面这个方法能正常获取
	// QHostInfo myself = QHostInfo::fromName(QHostInfo::localHostName());
	// QList<QHostAddress> addrs = myself.addresses();
	QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
	QStringList outputs;
	for (const QHostAddress &addr: addrs)
	{
		if (addr.protocol() == QAbstractSocket::IPv4Protocol)
		{
			QString output = QString("socat UDP6-LISTEN:%1,bind=[%0],reuseaddr,fork UDP4:%2:%3").arg(serverIPV6).
					arg(serverIPV6Port).arg(addr.toString()).arg(serverIPV4Port);
			std::cout << output.toStdString() << std::endl;
		}
	}
	return 0;
}
