#pragma once
#include "connectioninfo.h"

namespace User{
    enum Role{
        ADMIN,
        STUDENT,
        TEACHER,
        OUTCOME
    };

    enum Status{
        Normal,
        Exhausted,
        Banned
    };

}

class UserInfo
{
private:
    unsigned long long user_id;
    User::Role user_role;
    User::Status user_status;
    unsigned int borrowed_num;
	ConnectionInfo connection_info;
public:
    UserInfo(unsigned long long user_id, User::Role user_role, User::Status user_status, ConnectionInfo conn);
    UserInfo();
};

class AdminInfo
{
private:
	unsigned long long admin_id;
	QString admin_name;
	ConnectionInfo connection_info;
    QString post_info;
	QString work_status;
    
public:
	AdminInfo(unsigned long long admin_id, QString admin_name, ConnectionInfo connection_info, 
        QString post_info = "", QString work_status = "");
	AdminInfo();
    
	unsigned long long get_admin_id();
	QString get_admin_name();
	ConnectionInfo get_connection_info();
	QString get_post_info();
	QString get_work_status();

	void set_admin_name(QString admin_name);
	void set_connection_info(ConnectionInfo connection_info);
	void set_post_info(QString post_info);
	void set_work_status(QString work_status);

	void change_admin_info(QString admin_name, ConnectionInfo connection_info);
	void change_admin_info(AdminInfo admin_info);
};

