#include "buyerwindow.h"

BuyerWindow::BuyerWindow(Buyer *putBuyer, std::vector<Item*> putItems)
	:UserWindow(putBuyer, putItems), buyer(putBuyer)
{
	this->setWindowTitle(QStringLiteral("买家窗口"));
	ui.welcomeLabel->setText(QStringLiteral("尊敬的买家用户，欢迎登陆电商系统！"));

	topUpBtn = new QPushButton(QStringLiteral("充值"), this);
	this->ui.horizontalLayout_1->insertWidget(3,topUpBtn);
	connect(topUpBtn, &QPushButton::clicked, this, &BuyerWindow::topUp);

	//buyDialog = new BuyDialog(this->items, this->buyer, this);
	//buyDialog->hide();
	//connect(buyDialog, &BuyDialog::buySignal, this, &BuyerWindow::freshItems);

	buyBtn = new QPushButton(QStringLiteral("购买"),this);
	this->ui.verticalLayout->addWidget(buyBtn);
	connect(buyBtn, &QPushButton::clicked, this, &BuyerWindow::buyClicked);
}

BuyerWindow::~BuyerWindow()
{
	delete topUpBtn;
	delete buyBtn;
	//delete buyDialog;
}

void BuyerWindow::topUp()
{
	bool ok;
	float input = QInputDialog::getDouble(this, QStringLiteral("充值"),
		QStringLiteral("请输入充值金额："), 0, 0, 100000, 2, &ok);
	if (ok)
	{
		emit topUpSignal(buyer->getId(), input);
		if (this->buyer->topUp(input))
			QMessageBox::about(this, " ", QStringLiteral("充值成功！"));
		else
			QMessageBox::about(this, " ", QStringLiteral("充值失败！"));
	}
}

void BuyerWindow::buyClicked()
{
	//buyDialog->fresh();
	//buyDialog->show();
	BuyDialog buyDialog(this->items, this->buyer, this);
	connect(&buyDialog, &BuyDialog::buySignal, this, &BuyerWindow::freshItems);
	buyDialog.exec();
}

void BuyerWindow::freshItems()
{
	this->clearItems();
	this->showItems();
}