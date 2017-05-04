#include "user.h"
#include "qdebug.h"

User::User()
	:id(""), userName(""), password(""), type(user)
{
}

User::User(QString putId, QString putName, QString putPassword, float putBalance)
	: id(putId), userName(putName), password(putPassword), type(user)
{
	if (putBalance >= 0)
		balance = putBalance;
	else
		balance = 0;
}

User::~User()
{
}