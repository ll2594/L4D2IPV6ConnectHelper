#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class UdpForwarder;
QT_BEGIN_NAMESPACE

namespace Ui
{
	class Widget;
}

QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);

	~Widget();

private:
	void getServerIPV6();
	void link();
private:
	Ui::Widget *ui;
	UdpForwarder *udp6to4 = nullptr;
};
#endif // WIDGET_H
