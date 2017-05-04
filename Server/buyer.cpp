#include "buyer.h"

Buyer::Buyer()
	:User(), cost(0)
{
}

Buyer::Buyer(QString putId, QString putName, QString putPassword, float putBalance)
	:User(putId, putName, putPassword, putBalance), cost(0)
{
	this->type = buyer;
}


Buyer::~Buyer()
{
}

bool Buyer::topUp(const float value)
{
	if (value >= 0)
	{
		balance = balance + value;
		return true;
	}
	else
	{
		qDebug() << "ERROR:value<0;" << endl;
		return false;
	}
}

bool Buyer::buy(Item *item, float price, const unsigned int num)
{
	if (this->getBalance() >= price * num)
	{
		this->balance -= price * num;
		this->cost += price * num;
		/*
		switch (item->getStrType)
		{
		case food:
			FoodItem *tmpFood;
			//tmpFood = item;
			this->buyerItems.push_back();
		}*/
		return true;
	}
	else
	{
		qDebug() << "ERROR:cant afford;" << endl;
		return false;
	}
}

QTextStream& operator<< (QTextStream& out, const Buyer& b)
{
	out << b.id << "," << b.userName << "," << b.password << "," << b.balance;
	return out;
}

QTextStream& operator>> (QTextStream& in, Buyer& b)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	if (dataList.size() == 4)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		b.id = dataList[0];
		b.userName = dataList[1];
		b.password = dataList[2];
		b.balance = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
	}
	else
		throw 2;
	return in;
}