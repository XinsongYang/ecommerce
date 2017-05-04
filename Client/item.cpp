#include "item.h"

Item::Item()
	: id(""), name(""), amount(0), price(0), owner(NULL), type(item)
{
}

Item::Item(QString putId, QString putName, unsigned int putAmount, float putPrice, User *putOnwer,
	QDate putValid, QDate putProduce)
	: id(putId), name(putName), amount(putAmount), price(putPrice), owner(putOnwer), type(item),
	validDate(putValid), produceDate(putProduce), isValid(putValid > QDate::currentDate())//此处‘<’自带重载
{
}


Item::~Item()
{
	//不delete User
}

void Item::setAmount(const unsigned int num)
{
	this->amount = num;
}

QString Item::getStrType()
{
	switch (this->type)
	{
	case item: 
		return QStringLiteral("全部");
	case food: 
		return QStringLiteral("食品");
	case electronic: 
		return QStringLiteral("电子");
	case living: 
		return QStringLiteral("生活");
	}
}

QDate stringToDate(QString date)
{
	QStringList dateList = date.split(".");
	if (dateList.size() == 3)
		return QDate(dateList[0].toInt(), dateList[1].toInt(), dateList[2].toInt());
	else
		return QDate();
}