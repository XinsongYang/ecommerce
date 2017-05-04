#pragma once

#include <QObject>
#include <QDate>
#include <qtextstream.h>
#include <qstringlist.h>
#include "user.h"

enum itemType {item,food,electronic,living};

class Item
{
public:
	Item();
	Item(QString putId, QString putName, unsigned int putAmount, float putPrice, User *putOnwer,
		QDate putValid, QDate putProduce);
	~Item();
	QString getId() { return id; };
	QString getName() { return name; };
	unsigned int getAmount() { return amount; };
	QString getStrAmount() { return QString::number(amount, 10); };
	float getPrice() { return price; };
	QString getStrPrice() { return QString::number(price); };
	User* getOwner() { return owner; };
	QString getOwnerId() { return ownerId; };
	QString getOwnerName() { return owner->getUserName(); };
	itemType getType() { return type; };
	QString getStrType();
	QDate getValidDate() { return validDate; };
	QDate getProduceDate() { return produceDate; };
	bool getIsValid() { return isValid; };

	void setAmount(const unsigned int num);
	virtual void setPrice() = 0;
	void setOnwer(User *putOnwer){ owner = putOnwer; };

protected:
	QString id;
	QString name;
	unsigned int amount;
	float price;
	User *owner;
	QString ownerId;
	QDate validDate;
	QDate produceDate;
	bool isValid;
	itemType type;
};

QDate stringToDate(QString date);