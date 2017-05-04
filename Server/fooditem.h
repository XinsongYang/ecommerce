#pragma once
#include "item.h"

class FoodItem :
	public Item
{
public:
	FoodItem();
	FoodItem(QString putId, QString putName, unsigned int putAmount, float putPrice, User* putOnwer,
		QDate putValid, QDate putProduce, QDate putSale, float putFactor);
	~FoodItem();

	friend QTextStream& operator<< (QTextStream& out, const FoodItem& f);
	friend QTextStream& operator>> (QTextStream& in, FoodItem& f);

	virtual void setPrice();

private:
	QDate saleDate;
	float saleFactor;
};

