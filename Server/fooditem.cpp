#include "fooditem.h"

FoodItem::FoodItem()
	:Item()
{
	this->type = food;
}

FoodItem::FoodItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
	QDate putValid, QDate putProduce, QDate putSale, float putFactor)
	:Item(putId, putName, putAmount, putPrice, putOnwer, putValid, putProduce),
	saleDate(putSale), saleFactor(putFactor)
{
	this->type = food;
	setPrice();
}


FoodItem::~FoodItem()
{
}

void FoodItem::setPrice()
{
	if (this->isValid)
	{
		if (QDate::currentDate() > saleDate)
		{
			int days = (QDate::currentDate().year() - saleDate.year()) * 365 +
				QDate::currentDate().dayOfYear() - saleDate.dayOfYear();
			this->price = (price * 0.5 > days * saleFactor) ? (price - days * saleFactor) : (price * 0.5);
		}
	}
}

QTextStream& operator<< (QTextStream& out, const FoodItem& f)
{
	out << f.id << "," << f.name << "," << f.amount << "," << f.price << "," << f.owner->getId() << ","
		<< f.validDate.toString("yyyy.MM.dd") << "," << f.produceDate.toString("yyyy.MM.dd") << ","
		<< f.saleDate.toString("yyyy.MM.dd") << "," << f.saleFactor;
	return out;
}



QTextStream& operator>> (QTextStream& in, FoodItem& f)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	//qDebug() << dataList.size();
	if (dataList.size() == 9)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		f.id = dataList[0];
		f.name = dataList[1];
		f.amount = (dataList[2].toInt() > 0) ? dataList[2].toInt() : 0;
		f.price = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
		f.ownerId = dataList[4];
		f.validDate = stringToDate(dataList[5]);
		f.produceDate = stringToDate(dataList[6]);
		f.saleDate = stringToDate(dataList[7]);
		f.saleFactor = dataList[8].toFloat();
		f.isValid = (f.validDate > QDate::currentDate());
	}
	else
		throw 2;
	return in;
}