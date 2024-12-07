#include "widget.h"
#include <QHostInfo>
#include <QMessageBox>
#include "ui_widget.h"
#include "UdpForwarder.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);

	/// 获取本地IPV6地址
	QHostInfo myself = QHostInfo::fromName(QHostInfo::localHostName());
	QList<QHostAddress> addrs = myself.addresses();
	for (const QHostAddress &addr: addrs)
	{
		if (addr.protocol() == QAbstractSocket::IPv6Protocol)
		{
			QString addrString = addr.toString();
			if (addrString.startsWith("fe80"))
			{
				continue;
			}
			ui->localipv6Addr->addItem(addrString);
		}
		else if (addr.protocol() == QAbstractSocket::IPv4Protocol)
		{
			ui->localIpv4Addr->addItem(addr.toString());
		}
	}
	if (ui->localIpv4Addr->count() == 0)
	{
		QMessageBox::critical(nullptr, "错误", "获取本机IPV4地址失败！");
		QApplication::exit(-1);
	}
	if (ui->localipv6Addr->count() == 0)
	{
		QMessageBox::critical(nullptr, "错误", "获取本机IPV6地址失败！");
		QApplication::exit(-1);
	}

	connect(ui->getServerIP, &QPushButton::clicked, this, &Widget::getServerIPV6);

	connect(ui->start, &QPushButton::clicked, this, &Widget::link);
}

Widget::~Widget()
{
	delete ui;
}


void Widget::getServerIPV6()
{
	QString hostname = ui->serverDomain->text();
	QHostInfo info = QHostInfo::fromName(hostname);
	QList<QHostAddress> addrs = info.addresses();

	ui->serverip->clear();
	for (const QHostAddress &addr: addrs)
	{
		if (addr.protocol() == QAbstractSocket::IPv6Protocol)
		{
			ui->serverip->setText(addr.toString());
		}
	}
	if (ui->serverip->text().isEmpty())
	{
		QMessageBox::critical(nullptr, "错误", "域名没有IPV6地址，请检查域名是否正确，或本机是否连接了带有公网IPV6的网络！");
	}
}

void Widget::link()
{
	delete udp6to4;
	try
	{
		udp6to4 = new UdpForwarder(ui->serverip->text(), ui->serverport->value(), ui->localIpv4Addr->currentText(),
		                           ui->localipv6Addr->currentText(), 11451, this);
	}
	catch (std::runtime_error &e)
	{
		QMessageBox::critical(nullptr, "错误", e.what());
	}
	ui->start->setEnabled(false);
	ui->linkCmd->setText(QString("connect %0:%1").arg(ui->localIpv4Addr->currentText(), "11451"));
}
