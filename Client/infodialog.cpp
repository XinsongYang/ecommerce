#include "infodialog.h"

InfoDialog::InfoDialog(User *user, QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(tr("info"));
	ui.setupUi(this);
	QString tmpStr("ID:");
	tmpStr.append(user->getId());
	ui.idLabel->setText(tmpStr);
	tmpStr = QStringLiteral("用户名:");
	tmpStr.append(user->getUserName());
	ui.nameLabel->setText(tmpStr);
	tmpStr = QStringLiteral("余额:");
	tmpStr.append(user->getStrBalance());
	ui.balanceLabel->setText(tmpStr);
}

InfoDialog::InfoDialog(VipBuyer *vipBuyer, QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(tr("info"));
	ui.setupUi(this);
	QString tmpStr("ID:");
	tmpStr.append(vipBuyer->getId());
	ui.idLabel->setText(tmpStr);
	tmpStr = QStringLiteral("用户名:");
	tmpStr.append(vipBuyer->getUserName());
	ui.nameLabel->setText(tmpStr);
	tmpStr = QStringLiteral("余额:");
	tmpStr.append(vipBuyer->getStrBalance());
	ui.balanceLabel->setText(tmpStr);
	tmpStr = QStringLiteral("代币:");
	tmpStr.append(QString::number(vipBuyer->getToken()));
	ui.layout->addWidget(new QLabel(tmpStr,this));
}

InfoDialog::~InfoDialog()
{
	//不要delete user
}
