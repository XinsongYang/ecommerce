#include "livingitem.h"

LivingItem::LivingItem()
	:Item()
{
	this->type = living;
}

LivingItem::LivingItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
	QDate putValid, QDate putProduce)
	:Item(putId, putName, putAmount, putPrice, putOnwer, putValid, putProduce)
{
	this->type = living;
}


LivingItem::~LivingItem()
{
}

void LivingItem::setPrice()
{
}

QTextStream& operator<< (QTextStream& out, const LivingItem& l)
{
	out << l.id << "," << l.name << "," << l.amount << "," << l.price << "," << l.owner->getId() << ","
		<< l.validDate.toString("yyyy.MM.dd") << "," << l.produceDate.toString("yyyy.MM.dd");
	return out;
}

QTextStream& operator>> (QTextStream& in, LivingItem& l)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	//qDebug() << dataList.size();
	if (dataList.size() == 7)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		l.id = dataList[0];
		l.name = dataList[1];
		l.amount = (dataList[2].toInt() > 0) ? dataList[2].toInt() : 0;
		l.price = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
		l.ownerId = dataList[4];
		l.validDate = stringToDate(dataList[5]);
		l.produceDate = stringToDate(dataList[6]);
		l.isValid = (l.validDate > QDate::currentDate());
	}
	else
		throw 2;
	return in;
}