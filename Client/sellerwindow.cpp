#include "sellerwindow.h"

SellerWindow::SellerWindow(Seller *putSeller, std::vector<Item*> putItems)
	:UserWindow(putSeller, putItems), seller(putSeller)
{
	this->setWindowTitle(QStringLiteral("卖家窗口"));
	ui.welcomeLabel->setText(QStringLiteral("尊敬的卖家用户，欢迎登陆电商系统！"));

	showBtn = new QPushButton(QStringLiteral("个人商品"), this);
	this->ui.horizontalLayout_1->insertWidget(3, showBtn);
	connect(showBtn, &QPushButton::clicked, this, &SellerWindow::showSellerItems);

	addBtn = new QPushButton(QStringLiteral("进货"), this);
	this->ui.verticalLayout->addWidget(addBtn);
	connect(addBtn, &QPushButton::clicked, this, &SellerWindow::addItem);
}

SellerWindow::~SellerWindow()
{
	delete addBtn;
	delete showBtn;
}

void SellerWindow::showSellerItems()
{
	SellerItemsDialog itemDialog(this->seller->getItems(),this);
	itemDialog.exec();
}

void SellerWindow::addItem()
{
	AddItemDialog addDialog(this->seller, this->items, this);
	connect(&addDialog, &AddItemDialog::addToItems, this, &SellerWindow::addToItems);
	/*BUG
	connect(&addDialog, &AddItemDialog::addFood, this, &UserWindow::emitAddFood);
	connect(&addDialog, &AddItemDialog::addElec, this, &UserWindow::emitAddElec);
	connect(&addDialog, &AddItemDialog::addLiving, this, &UserWindow::emitAddLiving);
	*/
	addDialog.exec();
	this->clearItems();
	this->showItems();
}

void SellerWindow::addToItems(Item* putItem)
{
	items.push_back(putItem);
	emit addItemSignal(putItem);
}