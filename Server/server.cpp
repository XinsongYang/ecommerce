#include "server.h"

Server::Server()
{
	this->readData();

	receiver = new QUdpSocket(this);
	receiver->bind(QHostAddress::LocalHost, 6665);
	connect(receiver, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

	sender = new QUdpSocket(this);
}

template <class T>
void deleteV(std::vector<T*> v)
{
	for (std::vector<T*>::iterator it = v.begin(); it != v.end(); it++)
		delete *it;
}

Server::~Server()
{
	this->saveData();

	deleteV(this->buyers);
	deleteV(this->sellers);
	deleteV(this->vipBuyers);
	deleteV(this->foodItems);
	deleteV(this->elecItems);
	deleteV(this->livingItems);

	delete receiver;
	delete sender;
}

Seller* Server::getSeller(QString id)
{
	for (std::vector<Seller*>::iterator it = sellers.begin(); it != sellers.end(); it++)
		if ((*it)->getId() == id) return *it;
	return NULL;
}

QDate stringToDate(QString date)
{
	QStringList dateList = date.split(".");
	if (dateList.size() == 3)
		return QDate(dateList[0].toInt(), dateList[1].toInt(), dateList[2].toInt());
	else
		return QDate();
}

void Server::readData()
{
	QFile sellerData("sellers.txt");
	if (sellerData.open(QFile::ReadOnly))
	{
		QTextStream in(&sellerData);
		QString tmpStr = "";
		while (!in.atEnd())
		{
			Seller *tmpSeller = new Seller();
			in >> *tmpSeller;
			this->sellers.push_back(tmpSeller);
		}
	}
	else
		throw 1;
	sellerData.close();


	QFile buyerData("buyers.txt");
	if (buyerData.open(QFile::ReadOnly))
	{
		QTextStream in(&buyerData);
		while (!in.atEnd())
		{
			Buyer *tmpBuyer = new Buyer();
			in >> *tmpBuyer;
			this->buyers.push_back(tmpBuyer);
		}
	}
	else
		throw 1;
	buyerData.close();

	QFile vipData("vipBuyers.txt");
	if (vipData.open(QFile::ReadOnly))
	{
		QTextStream in(&vipData);
		while (!in.atEnd())
		{
			VipBuyer *tmpVip = new VipBuyer();
			in >> *tmpVip;
			this->vipBuyers.push_back(tmpVip);
		}
	}
	else
		throw 1;
	vipData.close();

	QFile foodData("foodItems.txt");
	if (foodData.open(QFile::ReadOnly))
	{
		QTextStream in(&foodData);
		while (!in.atEnd())
		{
			FoodItem *tmpFood = new FoodItem();
			in >> *tmpFood;
			tmpFood->setOnwer(getSeller(tmpFood->getOwnerId()));
			//tmpFood->setPrice();
			foodItems.push_back(tmpFood);
			items.push_back(tmpFood);
			getSeller(tmpFood->getOwnerId())->addItems(tmpFood);
		}
	}
	else
		throw 1;
	foodData.close();

	QFile elecData("elecItems.txt");
	if (elecData.open(QFile::ReadOnly))
	{
		QTextStream in(&elecData);
		while (!in.atEnd())
		{
			ElecItem *tmpElec = new ElecItem();
			in >> *tmpElec;
			tmpElec->setOnwer(getSeller(tmpElec->getOwnerId()));
			//tmpElec->setPrice();
			elecItems.push_back(tmpElec);
			items.push_back(tmpElec);
			getSeller(tmpElec->getOwnerId())->addItems(tmpElec);
		}
	}
	else
		throw 1;
	elecData.close();

	QFile livingData("livingItems.txt");
	if (livingData.open(QFile::ReadOnly))
	{
		QTextStream in(&livingData);
		while (!in.atEnd())
		{
			LivingItem *tmpLiving = new LivingItem();
			in >> *tmpLiving;
			tmpLiving->setOnwer(getSeller(tmpLiving->getOwnerId()));
			livingItems.push_back(tmpLiving);
			items.push_back(tmpLiving);
			getSeller(tmpLiving->getOwnerId())->addItems(tmpLiving);
		}
	}
	else
		throw 1;
	livingData.close();
}

void Server::saveData()
{
	QFile foodData("foodItems.txt");
	if (foodData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&foodData);
		std::vector<FoodItem*>::iterator it = foodItems.begin();
		out << **it;
		for (it = it + 1; it != foodItems.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open foodItems.txt";
	foodData.close();

	QFile elecData("elecItems.txt");
	if (elecData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&elecData);
		std::vector<ElecItem*>::iterator it = elecItems.begin();
		out << **it;
		for (it = it + 1; it != elecItems.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open elecItems.txt";
	elecData.close();

	QFile livingData("livingItems.txt");
	if (livingData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&livingData);
		std::vector<LivingItem*>::iterator it = livingItems.begin();
		out << **it;
		for (it = it + 1; it != livingItems.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open livingItems.txt";
	livingData.close();


	QFile sellerData("sellers.txt");
	if (sellerData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&sellerData);
		std::vector<Seller*>::iterator it = sellers.begin();
		out << **it;
		for (it = it + 1; it != sellers.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open sellers.txt";
	sellerData.close();


	QFile buyerData("buyers.txt");
	if (buyerData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&buyerData);
		std::vector<Buyer*>::iterator it = buyers.begin();
		out << **it;
		for (it = it + 1; it != buyers.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open buyers.txt";
	buyerData.close();


	QFile vipData("vipBuyers.txt");
	if (vipData.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(&vipData);
		std::vector<VipBuyer*>::iterator it = vipBuyers.begin();
		out << **it;
		for (it = it + 1; it != vipBuyers.end(); it++)
			out << endl << **it;
	}
	else
		qDebug() << "cant open vipBuyers.txt";
	vipData.close();
}

void Server::readPendingDatagrams()
{
	while (receiver->hasPendingDatagrams()) 
	{
		QByteArray datagram;
		datagram.resize(receiver->pendingDatagramSize());
		receiver->readDatagram(datagram.data(), datagram.size());
		qDebug() << "receive:" << datagram.data();

		QString str = datagram;
		QStringList dataList = str.split(" ");
		if (dataList[1] == "LOG" && dataList.size() == 5)
			verify(dataList);
		else if (dataList[1] == "TOP" && dataList.size() == 4)
			topUp(dataList);
		else if (dataList[0] == "BUY" && dataList.size() == 4)
			buy(dataList);
	}
}

void Server::verify(QStringList logList)
{
	quint16 clientPort = logList[0].toInt();
	qDebug() << "verify:clientPort" << clientPort;

	if (logList[2] == QStringLiteral("Âò¼Ò"))
	{
		for (std::vector<Buyer*>::iterator it = buyers.begin(); it != buyers.end(); it++)
		{
			if ((*it)->getId() == logList[3] && (*it)->getPassword() == logList[4])
			{
				qDebug() << "verify:buyer right" << endl;

				sendItems(clientPort);

				QByteArray buyerInfo = "LOG buyer ";
				buyerInfo.append((*it)->getId()).append(" ").append((*it)->getUserName()).append(" ")
					.append((*it)->getPassword()).append(" ").append((*it)->getStrBalance());

				sender->writeDatagram(buyerInfo, buyerInfo.size(), QHostAddress::LocalHost, clientPort);

				return;
			}
		}
		for (std::vector<VipBuyer*>::iterator it = vipBuyers.begin(); it != vipBuyers.end(); it++)
		{
			if ((*it)->getId() == logList[3] && (*it)->getPassword() == logList[4])
			{
				qDebug() << "vipbuyer right" << endl;
				
				sendItems(clientPort);
				
				QByteArray vipInfo = "LOG vipBuyer ";
				vipInfo.append((*it)->getId()).append(" ").append((*it)->getUserName()).append(" ")
					.append((*it)->getPassword()).append(" ").append((*it)->getStrBalance()).append(" ")
					.append(QString::number((*it)->getLevel())).append(" ").append(QString::number((*it)->getToken()));
				
				sender->writeDatagram(vipInfo, vipInfo.size(), QHostAddress::LocalHost, clientPort);
				
				return;
			}
		}
	}
	else if (logList[2] == QStringLiteral("Âô¼Ò"))
	{
		for (std::vector<Seller*>::iterator it = sellers.begin(); it != sellers.end(); it++)
		{
			if ((*it)->getId() == logList[3] && (*it)->getPassword() == logList[4])
			{
				qDebug() << "seller right" << endl;

				sendItems(clientPort);
				
				QByteArray sellerInfo = "LOG seller ";
				sellerInfo.append((*it)->getId()).append(" ").append((*it)->getUserName()).append(" ")
					.append((*it)->getPassword()).append(" ").append((*it)->getStrBalance());
				
				sender->writeDatagram(sellerInfo, sellerInfo.size(), QHostAddress::LocalHost, clientPort);
				
				return;
			}
		}
	}

	qDebug() << "wrong";
	sender->writeDatagram("LOG wrong", 9, QHostAddress::LocalHost, clientPort);
}

void Server::sendItems(quint16 port)
{
	QFile foodData("foodItems.txt");
	if (foodData.open(QFile::ReadOnly))
	{
		QTextStream in(&foodData);
		QByteArray foodInfo = "ITEMS food ";
		foodInfo.append(in.readAll());
		sender->writeDatagram(foodInfo, QHostAddress::LocalHost, port);
	}
	foodData.close();

	QFile elecData("elecItems.txt");
	if (elecData.open(QFile::ReadOnly))
	{
		QTextStream in(&elecData);
		QByteArray elecInfo = "ITEMS elec ";
		elecInfo.append(in.readAll());
		sender->writeDatagram(elecInfo, QHostAddress::LocalHost, port);
	}
	elecData.close();

	QFile livingData("livingItems.txt");
	if (livingData.open(QFile::ReadOnly))
	{
		QTextStream in(&livingData);
		QByteArray livingInfo = "ITEMS living ";
		livingInfo.append(in.readAll());
		sender->writeDatagram(livingInfo, QHostAddress::LocalHost, port);
	}
	livingData.close();
}

void Server::topUp(QStringList topList)
{
	for (std::vector<Buyer*>::iterator it = buyers.begin(); it != buyers.end(); it++)
	{
		if ((*it)->getId() == topList[2])
		{
			if ((*it)->topUp(topList[3].toFloat()))
				qDebug() << "topUp:" << (*it)->getId() << " " << (*it)->getBalance();
			return;
		}
	}
	for (std::vector<VipBuyer*>::iterator it = vipBuyers.begin(); it != vipBuyers.end(); it++)
	{
		if ((*it)->getId() == topList[2])
		{
			if ((*it)->topUp(topList[3].toFloat()))
				qDebug() << "topUp:" << (*it)->getId() << " " << (*it)->getBalance();
			return;
		}
	}
}

void Server::buy(QStringList buyList)
{
	Item *tmpItem;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getId() == buyList[2])
			tmpItem = *it;
	}

	for (std::vector<Buyer*>::iterator it = buyers.begin(); it != buyers.end(); it++)
	{
		if ((*it)->getId() == buyList[1])
		{
			(*it)->buy(tmpItem, tmpItem->getPrice(), buyList[3].toInt());
			tmpItem->setAmount(tmpItem->getAmount() - buyList[3].toInt());
			qDebug() << "buyItem amount:" << tmpItem->getAmount();
			tmpItem->getOwner()->setBalance(tmpItem->getOwner()->getBalance() + tmpItem->getPrice() * buyList[3].toInt());
			saveData();
			for (quint16 port = 6000; port < 6004; port++)
			{
				//QByteArray clear = "CLEAR", fresh = "FRESH";
				sender->writeDatagram("CLEAR", QHostAddress::LocalHost, port);
				sendItems(port);
				sender->writeDatagram("FRESH", QHostAddress::LocalHost, port);
			}
				
			return;
		}
	}

	for (std::vector<VipBuyer*>::iterator it = vipBuyers.begin(); it != vipBuyers.end(); it++)
	{
		if ((*it)->getId() == buyList[1])
		{
			(*it)->buy(tmpItem, tmpItem->getPrice(), buyList[3].toInt());
			tmpItem->setAmount(tmpItem->getAmount() - buyList[3].toInt());
			tmpItem->getOwner()->setBalance(tmpItem->getOwner()->getBalance() + tmpItem->getPrice() * buyList[3].toInt());
			saveData();
			for (quint16 port = 6000; port < 6004; port++)
			{
				sender->writeDatagram("CLEAR", QHostAddress::LocalHost, port);
				sendItems(port);
				sender->writeDatagram("FRESH", QHostAddress::LocalHost, port);
			}
			return;
		}
	}

}