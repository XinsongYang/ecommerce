#include "vipbuyer.h"

VipBuyer::VipBuyer()
	:Buyer(), level(0), token(0)
{
}

VipBuyer::VipBuyer(QString putId, QString putName, QString putPassword, float putBalance, unsigned int putLevel, float putToken)
	:Buyer(putId, putName, putPassword, putBalance), level(putLevel), token(putToken)
{
}


VipBuyer::~VipBuyer()
{
}

void VipBuyer::setToken(float putToken)
{
	if (putToken > 0)
		token = putToken;
	else
		token = 0;
}

QTextStream& operator<< (QTextStream& out, const VipBuyer& v)
{
	out << v.id << "," << v.userName << "," << v.password << "," << v.balance << "," << v.level << "," << v.token;
	return out;
}

QTextStream& operator>> (QTextStream& in, VipBuyer& v)
{
	QString tmpStr;
	in >> tmpStr;
	QStringList dataList = tmpStr.split(",");
	//qDebug() << dataList.size();
	if (dataList.size() == 6)
	{
		//qDebug() << dataList[0] << "," << dataList[1] << "," << dataList[2] << "," << dataList[3];
		v.id = dataList[0];
		v.userName = dataList[1];
		v.password = dataList[2];
		v.balance = (dataList[3].toFloat() > 0) ? dataList[3].toFloat() : 0;
		v.level = (dataList[4].toInt() > 0) ? dataList[4].toInt() : 0;
		v.token = (dataList[5].toFloat() > 0) ? dataList[5].toFloat() : 0;
	}
	else
		throw 2;
	return in;
}