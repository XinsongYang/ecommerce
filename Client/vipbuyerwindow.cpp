#include "vipbuyerwindow.h"

VipBuyerWindow::VipBuyerWindow(VipBuyer *putVip, std::vector<Item*> putItems)
	: BuyerWindow(putVip, putItems), vipBuyer(putVip)
{
	this->setWindowTitle(QStringLiteral("VIP买家窗口"));
	ui.welcomeLabel->setText(QStringLiteral("尊贵的VIP买家用户，欢迎登陆电商系统！"));

	tokenUpBtn = new QPushButton(QStringLiteral("充代币"), this);
	this->ui.horizontalLayout_1->insertWidget(4, tokenUpBtn);
	connect(tokenUpBtn, &QPushButton::clicked, this, &VipBuyerWindow::tokenUp);

	tokenConvertBtn = new QPushButton(QStringLiteral("代币兑换"), this);
	this->ui.horizontalLayout_1->insertWidget(5, tokenConvertBtn);
	connect(tokenConvertBtn, &QPushButton::clicked, this, &VipBuyerWindow::convert);
}

VipBuyerWindow::~VipBuyerWindow()
{

}

void VipBuyerWindow::showUser()
{
	InfoDialog infoDialog(vipBuyer, this);
	infoDialog.exec();
}

void VipBuyerWindow::buyClicked()
{
	BuyDialog buyDialog(this->items, this->buyer, this);
	connect(&buyDialog, &BuyDialog::buySignal, this, &BuyerWindow::freshItems);
	connect(&buyDialog, &BuyDialog::buySignal, this, &VipBuyerWindow::getToken);
	buyDialog.exec();
}

void VipBuyerWindow::tokenUp()
{
	bool ok;
	float input = QInputDialog::getDouble(this, QStringLiteral("充值"),
		QStringLiteral("请输入代币充值数额："), 0, 0, 100000, 2, &ok);
	if (ok)
	{
		if (input >= 0)
		{
			vipBuyer->setToken(vipBuyer->getToken() + input);
			QMessageBox::about(this, " ", QStringLiteral("充代币成功！"));
		}
		else
			QMessageBox::about(this, " ", QStringLiteral("充代币失败！"));
	}
}

void VipBuyerWindow::convert()
{
	bool ok;
	float input = QInputDialog::getDouble(this, QStringLiteral("充值"),
		QStringLiteral("代币兑换余额比例为10：1，请输入兑换数额："), 0, 0, vipBuyer->getToken(), 2, &ok);
	if (ok)
	{
		if (input >= 0)
		{
			vipBuyer->topUp(input / 10);
			vipBuyer->setToken(vipBuyer->getToken() - input);
			QMessageBox::about(this, " ", QStringLiteral("兑换成功！"));
		}
		else
			QMessageBox::about(this, " ", QStringLiteral("兑换失败！"));
	}
}

void VipBuyerWindow::getToken(float cost)
{
	vipBuyer->setToken(vipBuyer->getToken() + cost / 10);
	QString tmpStr(QStringLiteral("获得"));
	tmpStr.append(QString::number(cost / 10));
	tmpStr.append(QStringLiteral("代币"));
	//QMessageBox::about(this, " ", tmpStr);
}