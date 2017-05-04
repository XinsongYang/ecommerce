#include "client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Client client;
	QObject::connect(&client, &Client::closeSignal, &a, &QApplication::quit);

	return a.exec();
}
