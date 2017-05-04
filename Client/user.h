#pragma once

#include <QObject>
#include <QTextStream>
#include "qstringlist.h"
#include "qdebug.h"

enum userType {user,buyer,vipBuyer,seller};

class User
{
public:
	User();
	User(QString putId, QString putName, QString putPassword, float putBalance);
	~User();

	QString getId() { return id; };
	QString getUserName() { return userName; };
	QString getPassword() { return password; };
	float getBalance() { return balance; };
	QString getStrBalance() { return QString::number(balance); };
	userType getType() { return type; };

	void setBalance(float value) { balance = (value > 0) ? value : 0; };
	//void addItems(Item* putItem) { this->sellerItems.push_back(putItem); };

protected:
	QString id;
	QString userName;
	QString password;
	float balance;
	userType type;
	//命名有误，由于之前是放在Seller中的，改动起来太麻烦，并且Buyer也没有用到，故不改了
	//std::vector<Item*> sellerItems;
};

