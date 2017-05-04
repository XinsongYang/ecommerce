#pragma once
#include "item.h"

class ElecItem :
	public Item
{
public:
	ElecItem();
	ElecItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
		QDate putValid, QDate putProduce, float putFactor);
	~ElecItem();

	friend QTextStream& operator<< (QTextStream& out, const ElecItem& e);
	friend QTextStream& operator>> (QTextStream& in, ElecItem& e);

	virtual void setPrice();

private:
	float saleFactor;
};

