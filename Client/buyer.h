#pragma once
#include "user.h"
#include "item.h"

//extern class Item;

class Buyer :
	public User
{
public:
	Buyer();
	Buyer(QString putId, QString putName, QString putPassword, float putBalance);
	~Buyer();

	friend QTextStream& operator<< (QTextStream& out, const Buyer& b);
	friend QTextStream& operator>> (QTextStream& in, Buyer& b);


	bool topUp(const float value);
	bool buy(Item *item, float price, const unsigned int num);

protected:
	std::vector<Item*> buyerItems;
	float cost;
};

