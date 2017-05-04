#ifndef SELLERWINDOW_H
#define SELLERWINDOW_H

#include "userwindow.h"
#include "seller.h"
#include "selleritemsdialog.h"
#include "additemdialog.h"

class SellerWindow : public UserWindow
{
	Q_OBJECT

public:
	SellerWindow(Seller *putSeller, std::vector<Item*> putItems);
	~SellerWindow();

	void showSellerItems();
	void addItem();
	void addToItems(Item* putItem);

private:
	Seller *seller;
	QPushButton *addBtn;
	QPushButton *showBtn;
};

#endif // SELLERWINDOW_H
