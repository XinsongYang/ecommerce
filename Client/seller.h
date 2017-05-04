#pragma once
#include "user.h"
#include "item.h"

class Seller :
	public User
{
public:
	Seller();
	Seller(QString putId, QString putName, QString putPassword, float putBalance);
	~Seller();

	friend QTextStream& operator<< (QTextStream& out, const Seller& s);
	friend QTextStream& operator>> (QTextStream& in, Seller& s);

	std::vector<Item*> getItems(){ return sellerItems; };
	void addItems(Item* putItem) { this->sellerItems.push_back(putItem); };
	//float getIncome(){ return income; };

	void showOwned();

private:
	std::vector<Item*> sellerItems;
	//float income;
};

