#include "userwindow.h"
#include "qdebug.h"

/*UserWindow::UserWindow()
	//: 
{
	ui.setupUi(this);
	connect(ui.infoButton, &QPushButton::clicked, this, &UserWindow::showUser);
	connect(ui.logOutButton, &QPushButton::clicked, this, &UserWindow::logOut);
}*/

UserWindow::UserWindow(User *putUser, std::vector<Item*> putItems)
	:user(putUser), items(putItems)
{
	ui.setupUi(this);

	this->showItems();

	connect(ui.infoButton, &QPushButton::clicked, this, &UserWindow::showUser);
	connect(ui.logOutButton, &QPushButton::clicked, this, &UserWindow::logOut);
	connect(ui.searchButton, &QPushButton::clicked, this, &UserWindow::search);
	connect(ui.typeBox, &QComboBox::currentTextChanged, this, &UserWindow::search);
}

UserWindow::~UserWindow()
{
	//不要delete user，因为user指向的对象依然存在于logDialog

	for (std::vector<QTableWidgetItem*>::iterator it = tableItems.begin(); it != tableItems.end(); it++)
		delete *it;
}

void UserWindow::showUser()
{
	InfoDialog infoDialog(this->user, this);
	infoDialog.exec();
}

void UserWindow::showItems()
{
	int i = 0;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getIsValid() && (*it)->getAmount() > 0)
		{
			tableItems.push_back(new QTableWidgetItem((*it)->getStrType()));
			tableItems.push_back(new QTableWidgetItem((*it)->getId()));
			tableItems.push_back(new QTableWidgetItem((*it)->getName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getProduceDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getValidDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getOwnerId()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrAmount()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrPrice()));
			
			ui.itemTableWidget->insertRow(i);
			for (int j = 0; j < COLUMN; j++)
			{
				tableItems[i * COLUMN + j]->setTextAlignment(Qt::AlignCenter);
				tableItems[i * COLUMN + j]->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				ui.itemTableWidget->setItem(i, j, tableItems[i * COLUMN + j]);
			}
			i++;
		}
	}
}

void UserWindow::showItems(QString keyWord)
{
	int i = 0;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getIsValid() && (*it)->getAmount() > 0 && ((*it)->getName().contains(keyWord) || (*it)->getId().contains(keyWord)) &&
			(ui.typeBox->currentIndex() == 0 || (*it)->getType() == ui.typeBox->currentIndex()))
		{
			tableItems.push_back(new QTableWidgetItem((*it)->getStrType()));
			tableItems.push_back(new QTableWidgetItem((*it)->getId()));
			tableItems.push_back(new QTableWidgetItem((*it)->getName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getProduceDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getValidDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getOwnerId()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrAmount()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrPrice()));

			ui.itemTableWidget->insertRow(i);
			for (int j = 0; j < COLUMN; j++)
			{
				tableItems[i * COLUMN + j]->setTextAlignment(Qt::AlignCenter);
				tableItems[i * COLUMN + j]->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				ui.itemTableWidget->setItem(i, j, tableItems[i * COLUMN + j]);
			}
			i++;
		}
	}
}

void UserWindow::clearItems()
{
	for (std::vector<QTableWidgetItem*>::iterator it = tableItems.begin(); it != tableItems.end(); it++)
		delete *it;
	for (int i = 0; i < this->items.size(); i++)
		ui.itemTableWidget->removeRow(0);
	tableItems.clear();
}

void UserWindow::logOut()
{
	emit logOutSignal();
}

void UserWindow::search()
{
	this->clearItems();
	this->showItems(ui.searchInput->text());
}