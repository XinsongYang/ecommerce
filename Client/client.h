#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtNetwork>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include "qdebug.h"

#include "user.h"
#include "buyer.h"
#include "seller.h"
#include "vipbuyer.h"
#include "item.h"
#include "fooditem.h"
#include "elecitem.h"
#include "livingitem.h"
#include "logdialog.h"
#include "userwindow.h"
#include "buyerwindow.h"
#include "sellerwindow.h"
#include "vipbuyerwindow.h"

class Client : public QObject
{
	Q_OBJECT

public:
	Client();
	~Client();

signals:
	void closeSignal();

public slots:
	void readPendingDatagrams();
	void sendLogInfo(QByteArray logData);
	void logOut();
	void sendTopUp(QString id, float balance);

private:
	int userType;
	Buyer *buyer;
	VipBuyer *vipBuyer;
	Seller *seller;
	std::vector<Item*> items;
	std::vector<FoodItem*> foodItems;
	std::vector<ElecItem*> elecItems;
	std::vector<LivingItem*> livingItems;

	LogDialog *log;
	UserWindow *window;
	
	QUdpSocket *sender;
	QUdpSocket *receiver;
};

#endif // CLIENT_H
