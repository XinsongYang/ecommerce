#include "elecitem.h"

ElecItem::ElecItem()
	:Item()
{
	this->type = electronic;
}

ElecItem::ElecItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
	QDate putValid, QDate putProduce, float putFactor)
	: Item(putId, putName, putAmount, putPrice, putOnwer, putValid, putProduce), saleFactor(putFactor)
{
	this->type = electronic;
}


ElecItem::~ElecItem()
{
}

void ElecItem::setPrice()
{
	if (this->isValid)
	{
		int days = (QDate::currentDate().year() - produceDate.year()) * 365 +
			QDate::currentDate().dayOfYear() - produceDate.dayOfYear();
		this->price = (price * 0.5 > days * saleFactor) ? (price - days * saleFactor) : (price * 0.5);
	}
}

QTextStream& operator<< (QTextStream& out, const ElecItem& e)
{
	out << e.id << "," << e.name << "," << e.amount << "," << e.price << "," << e.owner->getId() << ","
		<< e.validDate.toString("yyyy.MM.dd") << "," << e.produceDate.toString("yyyy.MM.dd") << "," << e.saleFactor;
	return out;
}

QTextStream& operator>> (QTextStream& in, ElecItem& e)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	//qDebug() << dataList.size();
	if (dataList.size() == 8)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		e.id = dataList[0];
		e.name = dataList[1];
		e.amount = (dataList[2].toInt() > 0) ? dataList[2].toInt() : 0;
		e.price = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
		e.ownerId = dataList[4];
		e.validDate = stringToDate(dataList[5]);
		e.produceDate = stringToDate(dataList[6]);
		e.saleFactor = dataList[7].toFloat();
		e.isValid = (e.validDate > QDate::currentDate());
	}
	else
		throw 2;
	return in;
}