#ifndef VIPBUYERWINDOW_H
#define VIPBUYERWINDOW_H

#include "buyerwindow.h"
#include "vipbuyer.h"
#include "item.h"

class VipBuyerWindow : public BuyerWindow
{
	Q_OBJECT

public:
	VipBuyerWindow(VipBuyer *putVip, std::vector<Item*> putItems);
	~VipBuyerWindow();

	virtual void showUser();
	virtual void buyClicked();
	void tokenUp();
	void convert();
	void getToken(float cost);

private:
	VipBuyer *vipBuyer;
	QPushButton *tokenUpBtn;
	QPushButton *tokenConvertBtn;
};

#endif // VIPBUYERWINDOW_H
