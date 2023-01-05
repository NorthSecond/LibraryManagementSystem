#pragma once

#include <QString>

class ConnectionInfo
{
	unsigned long long connection_id;
	QString telephone;
	QString email;
	QString address;
	QString postcode;

public:
	ConnectionInfo(unsigned long long connection_id, QString telephone, QString email, QString address, QString postcode);
	ConnectionInfo(QString telephone, QString email, QString address, QString postcode);
	ConnectionInfo(unsigned long long connection_id);
	ConnectionInfo(unsigned long long connection_id, QString telephone);
	ConnectionInfo(QString telephone);
	ConnectionInfo();
	//bool commitToDB();
	
	unsigned long long get_connection_id();
	QString get_telephone();
	QString get_email();
	QString get_address();
	QString get_postcode();
	
	void set_telephone(QString telephone);
	void set_email(QString email);
	void set_address(QString address);
	void set_postcode(QString postcode);
	
	void change_connection_info(QString telephone, QString email, QString address, QString postcode);
	void change_connection_info(ConnectionInfo connection_info);
};
