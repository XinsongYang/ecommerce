#ifndef BUYDIALOG_H
#define BUYDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include "ui_buydialog.h"
#include "item.h"
#include "User.h"
#include "buyer.h"
#include "qdebug.h"

class BuyDialog : public QDialog
{
	Q_OBJECT

public:
	BuyDialog(std::vector<Item*> putItems, Buyer* putBuyer, QWidget *parent = 0);
	~BuyDialog();

	void setPara(std::vector<Item*> putItems, Buyer* putUser);
	void fresh();
	void idChanged();
	void numChanged();
	void okClicked();

signals:
	void buySignal(float cost);

private:
	Ui::BuyDialog ui;
	std::vector<Item*> items;
	Buyer *buyer;
	Item *selectedItem;
	QString numStr;
	unsigned int selectedNum;
};

#endif // BUYDIALOG_H
