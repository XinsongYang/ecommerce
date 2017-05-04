#include "seller.h"

Seller::Seller()
	:User()
{
}

Seller::Seller(QString putId, QString putName, QString putPassword, float putBalance)
	:User(putId, putName, putPassword, putBalance)
{
	this->type = seller;
}


Seller::~Seller()
{
}

void Seller::showOwned()
{
}


QTextStream& operator<< (QTextStream& out, const Seller& s)
{
	out << s.id << "," << s.userName << "," << s.password << "," << s.balance;
	return out;
}

QTextStream& operator>> (QTextStream& in, Seller& s)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	if (dataList.size() == 4)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		s.id = dataList[0];
		s.userName = dataList[1];
		s.password = dataList[2];
		s.balance = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
	}
	else
		throw 2;
	return in;
}