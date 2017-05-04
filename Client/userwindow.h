#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QtWidgets/QWidget>
#include <QDate>
#include <qdialog.h>
#include "ui_userwindow.h"
#include "user.h"
#include "seller.h"
#include "infodialog.h"
#include "logdialog.h"
#include "item.h"
#include <QMessageBox>

const int COLUMN = 8;


class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(User *putUser, std::vector<Item*> putItems);
	~UserWindow();

	virtual void showUser();
	void showItems();
	void showItems(QString keyWordm);
	void clearItems();
	void logOut();
	void search();

signals:
	void logOutSignal();
	void topUpSignal(QString id, float balance);
	void addItemSignal(Item* putItem);

protected:
	Ui::UserWindowClass ui;
	User *user;
	std::vector<Item*> items;
	std::vector<QTableWidgetItem*> tableItems;	
};

#endif // USERWINDOW_H
