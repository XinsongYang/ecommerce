#ifndef BUYERWINDOW_H
#define BUYERWINDOW_H

#include "buyer.h"
#include "userwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <buydialog.h>
//#include "ui_buyerwindow.h"

class BuyerWindow : public UserWindow
{
	Q_OBJECT

public:
	BuyerWindow(Buyer *putBuyer, std::vector<Item*> putItems);
	~BuyerWindow();
	
	void topUp();
	virtual void buyClicked();
	void freshItems();

protected:
	Buyer* buyer;
	QPushButton *topUpBtn;
	QPushButton *buyBtn;
	//BuyDialog *buyDialog;
	//Ui::BuyerWindow ui;
};

#endif // BUYERWINDOW_H
