#include "logdialog.h"
#include <QMessageBox>
#include "qdebug.h"

LogDialog::LogDialog()
{
	ui.setupUi(this);

	connect(ui.logButton, &QPushButton::clicked, this, &LogDialog::clickLog);
}

LogDialog::~LogDialog()
{
}

void LogDialog::clickLog()
{
	QByteArray logData = "LOG";
	logData.append(" ");
	logData.append(ui.typeBox->currentText());
	logData.append(" ");
	logData.append(ui.idInput->text());
	logData.append(" ");
	logData.append(ui.passwordInput->text());

	emit logSignal(logData);
}

void LogDialog::logWrong()
{
	QMessageBox::about(this, QStringLiteral("错误"), QStringLiteral("用户名或密码错误，请重新输入。"));
	ui.passwordInput->clear();
	ui.idInput->clear();
	ui.idInput->setFocus();
}