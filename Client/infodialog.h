#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <qlabel.h>
#include "ui_infodialog.h"
#include "user.h"
#include "vipbuyer.h"

class InfoDialog : public QDialog
{
	Q_OBJECT

public:
	InfoDialog(User *user, QWidget *parent = 0);
	InfoDialog(VipBuyer *vipBuyer, QWidget *parent = 0);
	~InfoDialog();

private:
	Ui::InfoDialog ui;
};

#endif // INFODIALOG_H
