#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <qstring.h>
#include <qstringlist.h>
#include <QDebug>
#include <QFile>
#include <qtextstream.h>
#include <exception>
#include <QDate>
#include "user.h"
#include "buyer.h"
#include "seller.h"
#include "vipbuyer.h"
#include "item.h"
#include "fooditem.h"
#include "elecitem.h"
#include "livingitem.h"

QDate stringToDate(QString date);

class Server : public QObject
{
	Q_OBJECT

public:
	Server();
	~Server();

	Seller* getSeller(QString id);
	void readData();
	void saveData();
	void verify(QStringList logList);
	void sendItems(quint16 port);
	void topUp(QStringList topList);
	void buy(QStringList buyList);

private slots:
	void readPendingDatagrams();

private:
	std::vector<Buyer*> buyers;
	std::vector<VipBuyer*> vipBuyers;
	std::vector<Seller*> sellers;
	std::vector<FoodItem*> foodItems;
	std::vector<ElecItem*> elecItems;
	std::vector<LivingItem*> livingItems;
	std::vector<Item*> items;

	QUdpSocket *receiver;
	QUdpSocket *sender;
};

#endif // SERVER_H
