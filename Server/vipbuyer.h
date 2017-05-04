#pragma once
#include "buyer.h"

class VipBuyer :
	public Buyer
{
public:
	VipBuyer();
	VipBuyer(QString putId, QString putName, QString putPassword, float putBalance, unsigned int putLevel, float putToken);
	~VipBuyer();

	friend QTextStream& operator<< (QTextStream& out, const VipBuyer& v);
	friend QTextStream& operator>> (QTextStream& in, VipBuyer& v);

	unsigned int getLevel() { return level; };
	float getToken(){ return token; };
	void setToken(float putToken);

private:
	unsigned int level;
	float token;
};

