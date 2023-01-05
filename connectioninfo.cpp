#include "connectioninfo.h"


ConnectionInfo::ConnectionInfo(unsigned long long connection_id, QString telephone, QString email, QString address, QString postcode)
	: connection_id(connection_id), telephone(telephone), email(email), address(address), postcode(postcode)
{
}

ConnectionInfo::ConnectionInfo(QString telephone, QString email, QString address, QString postcode)
	: telephone(telephone), email(email), address(address), postcode(postcode)
{
}

ConnectionInfo::ConnectionInfo(unsigned long long connection_id)
	: connection_id(connection_id)
{
}

ConnectionInfo::ConnectionInfo(unsigned long long connection_id, QString telephone)
{
	this->connection_id = connection_id;
	this->telephone = telephone;
}

ConnectionInfo::ConnectionInfo()
{
}

unsigned long long ConnectionInfo::get_connection_id()
{
	return connection_id;
}

QString ConnectionInfo::get_telephone()
{
	return telephone;
}

QString ConnectionInfo::get_email()
{
	return email;
}

QString ConnectionInfo::get_address()
{
	return address;
}

QString ConnectionInfo::get_postcode()
{
	return postcode;
}

void ConnectionInfo::set_telephone(QString telephone)
{
	this->telephone = telephone;
}

void ConnectionInfo::set_email(QString email)
{
	this->email = email;
}

void ConnectionInfo::set_address(QString address)
{
	this->address = address;
}

void ConnectionInfo::set_postcode(QString postcode)
{
	this->postcode = postcode;
}

void ConnectionInfo::change_connection_info(QString telephone, QString email, QString address, QString postcode)
{
	this->telephone = telephone;
	this->email = email;
	this->address = address;
	this->postcode = postcode;
}

void ConnectionInfo::change_connection_info(ConnectionInfo connection_info)
{
	this->telephone = connection_info.get_telephone();
	this->email = connection_info.get_email();
	this->address = connection_info.get_address();
	this->postcode = connection_info.get_postcode();
}
