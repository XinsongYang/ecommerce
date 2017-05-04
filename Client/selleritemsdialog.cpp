#include "selleritemsdialog.h"

SellerItemsDialog::SellerItemsDialog(std::vector<Item*> putItems, QWidget *parent)
	: QDialog(parent), items(putItems)
{
	ui.setupUi(this);

	this->showItems();

	connect(ui.searchButton, &QPushButton::clicked, this, &SellerItemsDialog::search);
	connect(ui.typeBox, &QComboBox::currentTextChanged, this, &SellerItemsDialog::search);

	/*
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
			//tableItems.push_back(new QTableWidgetItem((*it)->getOwnerName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrAmount()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrPrice()));

			ui.tableWidget->insertRow(i);
			for (int j = 0; j < 7; j++)
			{
				tableItems[i * 7 + j]->setTextAlignment(Qt::AlignCenter);
				tableItems[i * 7 + j]->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				ui.tableWidget->setItem(i, j, tableItems[i * 7 + j]);
			}
			i++;
		}
	}
	*/
}

SellerItemsDialog::~SellerItemsDialog()
{
	for (std::vector<QTableWidgetItem*>::iterator it = tableItems.begin(); it != tableItems.end(); it++)
		delete *it;
}

void SellerItemsDialog::showItems()
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
			tableItems.push_back(new QTableWidgetItem((*it)->getOwnerName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrAmount()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrPrice()));

			ui.itemTableWidget->insertRow(i);
			const int COLUMN = 8;
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

void SellerItemsDialog::showItems(QString keyWord)
{
	int i = 0;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getIsValid() && (*it)->getAmount() > 0 && (*it)->getName().contains(keyWord) &&
			(ui.typeBox->currentIndex() == 0 || (*it)->getType() == ui.typeBox->currentIndex()))
		{
			tableItems.push_back(new QTableWidgetItem((*it)->getStrType()));
			tableItems.push_back(new QTableWidgetItem((*it)->getId()));
			tableItems.push_back(new QTableWidgetItem((*it)->getName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getProduceDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getValidDate().toString("yyyy,MM,dd")));
			tableItems.push_back(new QTableWidgetItem((*it)->getOwnerName()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrAmount()));
			tableItems.push_back(new QTableWidgetItem((*it)->getStrPrice()));

			ui.itemTableWidget->insertRow(i);
			const int COLUMN = 8;
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

void SellerItemsDialog::clearItems()
{
	for (std::vector<QTableWidgetItem*>::iterator it = tableItems.begin(); it != tableItems.end(); it++)
		delete *it;
	for (int i = 0; i < this->items.size(); i++)
		ui.itemTableWidget->removeRow(0);
	tableItems.clear();
}


void SellerItemsDialog::search()
{
	this->clearItems();
	this->showItems(ui.searchInput->text());
}