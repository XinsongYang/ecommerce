#include "buydialog.h"

BuyDialog::BuyDialog(std::vector<Item*> putItems, Buyer* putBuyer, QWidget *parent)
	: QDialog(parent), items(putItems), buyer(putBuyer)
{
	ui.setupUi(this);

	for (std::vector<Item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		ui.idBox->addItem((*it)->getId());
	selectedItem = *items.begin();
	this->fresh();

	connect(ui.idBox, &QComboBox::currentTextChanged, this, &BuyDialog::idChanged);
	connect(ui.numBox, &QComboBox::currentTextChanged, this, &BuyDialog::numChanged);
	connect(ui.okButton, &QPushButton::clicked, this, &BuyDialog::okClicked);
}

BuyDialog::~BuyDialog()
{
	//不要delete Item和User
}

void BuyDialog::fresh()
{
	QString balanceStr = QStringLiteral("账户余额：");
	balanceStr.append(buyer->getStrBalance());
	ui.balanceLabel->setText(balanceStr);
	
	//ui.idBox->clear()程序会出错，同时也没有必要更新idBox
	ui.numBox->clear();
	for (int i = 1; i <= this->selectedItem->getAmount(); i++)
	{
		if (i * selectedItem->getPrice() > buyer->getBalance())
			break;
		ui.numBox->addItem(QString::number(i, 10));
	}
	numStr = ui.numBox->currentText();
	this->selectedNum = numStr.toInt();
	float price = selectedItem->getPrice() * selectedNum;
	QString priceStr = QStringLiteral("     商品价格总计：");
	priceStr.append(QString::number(price));
	ui.priceLabel->setText(priceStr);
	//ui.idBox->setEditable(true);
	//ui.numBox->setEditable(true);
}

void BuyDialog::idChanged()
{
	selectedItem = this->items[ui.idBox->currentIndex()];
	ui.numBox->clear();
	//for (int i = 1; i <= ui.numBox->count(); i++)
		//ui.numBox->removeItem(i);
	for (int i = 1; i <= selectedItem->getAmount(); i++)
	{
		if (i * selectedItem->getPrice() > buyer->getBalance())
			break;
		ui.numBox->addItem(QString::number(i, 10));
	}
		
}

void BuyDialog::numChanged()
{
	numStr = ui.numBox->currentText();
	selectedNum = numStr.toInt();
	float price = selectedItem->getPrice() * selectedNum;
	QString priceStr = QStringLiteral("     商品价格总计：");
	priceStr.append(QString::number(price));
	ui.priceLabel->setText(priceStr);
}

void BuyDialog::okClicked()
{
	if (buyer->getBalance() >= selectedItem->getPrice() * selectedNum)
	{
		//qDebug() << this->selectedItem->getAmount();
		buyer->buy(selectedItem, selectedItem->getPrice(), selectedNum);
		//selectedItem->setAmount(selectedItem->getAmount() - selectedNum);
		//selectedItem->getOwner()->setBalance(selectedItem->getOwner()->getBalance() + selectedItem->getPrice() * selectedNum);
		//emit buySignal(selectedItem->getPrice() * selectedNum);

		QByteArray buyInfo = "BUY ";
		buyInfo.append(buyer->getId()).append(" ").append(selectedItem->getId()).append(" ").append(QString::number(selectedNum));
		QUdpSocket *sender = new QUdpSocket(this);
		
		qDebug() << "send:" << buyInfo.data();
		
		QMessageBox::about(this, QStringLiteral(" "), QStringLiteral("购买成功！"));
		sender->writeDatagram(buyInfo, QHostAddress::LocalHost, 6665);
	}
	else
		QMessageBox::about(this, QStringLiteral("错误"), QStringLiteral("余额不足，购买失败！"));
	this->close();
}