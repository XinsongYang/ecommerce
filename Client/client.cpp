#include "client.h"

Client::Client()
	:userType(0)
{
	//接收socket
	receiver = new QUdpSocket(this);

	//初始化端口号
	quint16 port = 6000;
	while (!receiver->bind(QHostAddress::LocalHost, port))
		port++;

	connect(receiver, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

	qDebug() << "port:" << receiver->localPort();
	
	//发送socket
	sender = new QUdpSocket(this);

	//登录窗
	log = new LogDialog();
	log->show();
	connect(log, &LogDialog::logSignal, this, &Client::sendLogInfo);
	connect(log, &LogDialog::destroyed, this, &Client::closeSignal);
}


//删除模版类vector
template <class T>
void deleteV(std::vector<T*> v)
{
	for (std::vector<T*>::iterator it = v.begin(); it != v.end(); it++)
		delete *it;
}

Client::~Client()
{
	delete log;
	delete window;
	delete receiver;
	delete sender;
	delete buyer;
	delete vipBuyer;
	delete seller;
	deleteV(this->foodItems);
	deleteV(this->elecItems);
	deleteV(this->livingItems);
}

//接收数据
void Client::readPendingDatagrams()
{
	while (receiver->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(receiver->pendingDatagramSize());
		receiver->readDatagram(datagram.data(), datagram.size());
		qDebug() << "receive:" << datagram.data();
		QString str = datagram;
		//数据均以空格为分割符
		QStringList dataList = str.split(" ");
		qDebug() << "size:" << dataList.size();

		//若为登录信息
		if (dataList[0] == "LOG")
		{
			//账号或密码错误
			if (dataList[1] == "wrong")
				log->logWrong();
			//买家用户
			else if (dataList[1] == "buyer" && dataList.size() == 6)
			{
				userType = 1;
				buyer = new Buyer(dataList[2], dataList[3], dataList[4], dataList[5].toFloat());
				window = new BuyerWindow(buyer, items);
				connect(window, &UserWindow::logOutSignal, this, &Client::logOut);
				connect(window, &UserWindow::topUpSignal, this, &Client::sendTopUp);
				
				window->show();
				log->hide();
			}
			//卖家用户
			else if (dataList[1] == "seller" && dataList.size() == 6)
			{
				userType = 2;
				seller = new Seller(dataList[2], dataList[3], dataList[4], dataList[5].toFloat());
				window = new SellerWindow(seller, items);
				connect(window, &UserWindow::logOutSignal, this, &Client::logOut);
				window->show();
				log->hide();
			}
			//vip用户
			else if (dataList[1] == "vipBuyer" && dataList.size() == 8)
			{
				userType = 3;
				vipBuyer = new VipBuyer(dataList[2], dataList[3], dataList[4], dataList[5].toFloat(),
					dataList[6].toInt(), dataList[7].toFloat());
				window = new VipBuyerWindow(vipBuyer, items);
				connect(window, &UserWindow::logOutSignal, this, &Client::logOut);
				connect(window, &UserWindow::topUpSignal, this, &Client::sendTopUp);
				
				window->show();
				log->hide();
			}
		}

		//若为商品信息
		else if (dataList[0] == "ITEMS" && dataList.size() == 3)
		{
			if (dataList[1] == "food")
			{
				QTextStream in(&dataList[2]);
				while (!in.atEnd())
				{
					//qDebug() << "fuck1";
					FoodItem *tmpFood = new FoodItem();
					in >> *tmpFood;
					foodItems.push_back(tmpFood);
					items.push_back(tmpFood);
				}
			}
			else if (dataList[1] == "elec")
			{
				QTextStream in(&dataList[2]);
				while (!in.atEnd())
				{
					//qDebug() << "fuck2";
					ElecItem *tmpElec = new ElecItem();
					in >> *tmpElec;
					elecItems.push_back(tmpElec);
					items.push_back(tmpElec);
				}
			}
			else if (dataList[1] == "living")
			{
				QTextStream in(&dataList[2]);
				while (!in.atEnd())
				{
					//qDebug() << "fuck3";
					LivingItem *tmpLiving = new LivingItem();
					in >> *tmpLiving;
					livingItems.push_back(tmpLiving);
					items.push_back(tmpLiving);
				}
			}
		}

		else if (str == "CLEAR")
		{
			qDebug() << "fuck:clear";
			//window->clearItems();
			delete window;
			deleteV(this->foodItems);
			deleteV(this->elecItems);
			deleteV(this->livingItems);
			foodItems.clear();
			elecItems.clear();
			livingItems.clear();
			items.clear();
		}

		else if (str == "FRESH")
		{
			qDebug() << "fuck:fresh";
			
			if (userType == 1)
				window = new BuyerWindow(buyer, items);
			else if (userType == 2)
				window = new SellerWindow(seller, items);
			else if (userType == 3)
				window = new VipBuyerWindow(vipBuyer, items);
			
			connect(window, &UserWindow::logOutSignal, this, &Client::logOut);
			connect(window, &UserWindow::topUpSignal, this, &Client::sendTopUp);

			window->show();
		}
	}
}

void Client::sendLogInfo(QByteArray logData)
{
	logData.prepend(" ");
	logData.prepend(QByteArray::number(receiver->localPort()));
	sender->writeDatagram(logData.data(), logData.size(), QHostAddress::LocalHost, 6665);
	qDebug() << "send:" << logData.data();
}

void Client::logOut()
{
	delete window;
	deleteV(this->foodItems);
	deleteV(this->elecItems);
	deleteV(this->livingItems);
	foodItems.clear();
	elecItems.clear();
	livingItems.clear();
	items.clear();
	//delete buyer;
	//delete vipBuyer;
	//delete seller;

	log->show();
}

void Client::sendTopUp(QString id, float balance)
{
	QByteArray topData = QByteArray::number(receiver->localPort());
	topData.append(" TOP ").append(id).append(" ").append(QString::number(balance));
	sender->writeDatagram(topData, QHostAddress::LocalHost, 6665);
	qDebug() << "send:" << topData.data();
}