#ifndef SELLERITEMSDIALOG_H
#define SELLERITEMSDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "ui_selleritemsdialog.h"
#include "item.h"

class SellerItemsDialog : public QDialog
{
	Q_OBJECT

public:
	SellerItemsDialog(std::vector<Item*> putItems, QWidget *parent = 0);
	~SellerItemsDialog();
	void showItems();
	void showItems(QString keyWordm);
	void clearItems();
	void search();

private:
	Ui::SellerItemsDialog ui;
	std::vector<Item*> items;
	std::vector<QTableWidgetItem*> tableItems;
};

#endif // SELLERITEMSDIALOG_H
