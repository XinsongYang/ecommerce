#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QByteArray>
#include "ui_logdialog.h"
#include <vector>
#include "user.h"
#include "buyer.h"
#include "vipbuyer.h"
#include "seller.h"

class LogDialog : public QDialog
{
	Q_OBJECT

public:
	LogDialog();
	~LogDialog();
	void logWrong();

	public slots:
	void clickLog();

signals:
	void logSignal(QByteArray logData);

private:
	Ui::LogDialog ui;
};

#endif // LOGDIALOG_H
