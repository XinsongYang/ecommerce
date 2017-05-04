#include "additemdialog.h"

AddItemDialog::AddItemDialog(Seller *putSeller, std::vector<Item*> putItems, QWidget *parent)
	: QDialog(parent), seller(putSeller), items(putItems)
{
	ui.setupUi(this);
	
	ui.numLineEdit->setValidator(new QIntValidator(1, 100000, this));
	ui.priceLineEdit->setValidator(new QDoubleValidator(0.01, 10000, 2, this));
	ui.factorLineEdit->setValidator(new QDoubleValidator(0.01, 1, 2, this));
	connect(ui.addButton, &QPushButton::clicked, this, &AddItemDialog::add);
	connect(ui.typeBox, &QComboBox::currentTextChanged, this, &AddItemDialog::typeChanged);
}

AddItemDialog::~AddItemDialog()
{

}

void AddItemDialog::typeChanged()
{
	switch (ui.typeBox->currentIndex())
	{
	case 0:
		ui.saleDateEdit->setEnabled(true);
		ui.factorLineEdit->setEnabled(true);
		break;
	case 1:
		ui.saleDateEdit->setEnabled(false);
		ui.factorLineEdit->setEnabled(true);
		break;
	case 2:
		ui.saleDateEdit->setEnabled(false);
		ui.factorLineEdit->setEnabled(false);
		break;
	}
}

void AddItemDialog::add()
{
	if (ui.validDateEdit->date() > QDate::currentDate())//待添加：如果输入正确
	{
		Item *tmpItem;
		switch (ui.typeBox->currentIndex())
		{
		case 0:
			tmpItem = new FoodItem(ui.iDLineEdit->text(), ui.nameLineEdit->text(), ui.numLineEdit->text().toInt(), 
				ui.priceLineEdit->text().toFloat(), this->seller, ui.validDateEdit->date(), ui.produceDateEdit->date(), 
				ui.saleDateEdit->date(), ui.factorLineEdit->text().toFloat());
			break;
		case 1:
			tmpItem = new ElecItem(ui.iDLineEdit->text(), ui.nameLineEdit->text(), ui.numLineEdit->text().toInt(),
				ui.priceLineEdit->text().toFloat(), this->seller, ui.validDateEdit->date(), ui.produceDateEdit->date(),
				ui.factorLineEdit->text().toFloat());
		case 2:
			tmpItem = new LivingItem(ui.iDLineEdit->text(), ui.nameLineEdit->text(), ui.numLineEdit->text().toInt(),
				ui.priceLineEdit->text().toFloat(), this->seller, ui.validDateEdit->date(), ui.produceDateEdit->date());
		}
		seller->addItems(tmpItem);
		emit addToItems(tmpItem);

		QMessageBox::about(this, " ", QStringLiteral("进货成功"));
		this->close();
	}
	else
		QMessageBox::about(this, " ", QStringLiteral("进货失败，请输入正确信息！"));
}