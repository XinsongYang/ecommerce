#pragma once
#include "item.h"

class LivingItem :
	public Item
{
public:
	LivingItem();
	LivingItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
		QDate putValid, QDate putProduce);
	~LivingItem();

	friend QTextStream& operator<< (QTextStream& out, const LivingItem& l);
	friend QTextStream& operator>> (QTextStream& in, LivingItem& l);

	virtual void setPrice();
};

