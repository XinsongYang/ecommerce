#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_additemdialog.h"
#include "item.h"
#include "fooditem.h"
#include "elecitem.h"
#include "livingitem.h"
#include "seller.h"

class AddItemDialog : public QDialog
{
	Q_OBJECT

public:
	AddItemDialog(Seller *putSeller, std::vector<Item*> putItems, QWidget *parent = 0);
	~AddItemDialog();

	void add();
	void typeChanged();

signals:
	void addToItems(Item *putItem);
	/*BUG
	void addFood(QString putId, QString putName, unsigned int putAmount, float putPrice, Seller* putOnwer,
		QDate putValid, QDate putProduce, QDate putSale, float putFactor);
	void addElec(QString putId, QString putName, unsigned int putAmount, float putPrice, Seller* putOnwer,
		QDate putValid, QDate putProduce, float putFactor);
	void addLiving(QString putId, QString putName, unsigned int putAmount, float putPrice, Seller* putOnwer,
		QDate putValid, QDate putProduce);
	*/

private:
	Ui::AddItemDialog ui;
	std::vector<Item*> items;
	Seller *seller;
};

#endif // ADDITEMDIALOG_H
