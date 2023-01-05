#include "userinfo.h"

UserInfo::UserInfo(unsigned long long user_id, QString user_name, User::Role user_role, User::Status user_status, ConnectionInfo conn)
{
	this->user_id = user_id;
	this->user_name = user_name;
	this->user_role = user_role;
	this->user_status = user_status;
	this->connection_info = conn;
}

UserInfo::UserInfo()
{
	this->user_id = 0;
	this->user_role = User::OUTCOME;
	this->user_status = User::Normal;
	this->connection_info = ConnectionInfo();
}

unsigned long long UserInfo::get_user_id()
{
	return this->user_id;
}

QString UserInfo::get_user_name()
{
	return this->user_name;
}

User::Role UserInfo::get_user_role()
{
	return this->user_role;
}

User::Status UserInfo::get_user_status()
{
	return this->user_status;
}

unsigned int UserInfo::get_borrowed_num()
{
	return this->borrowed_num;
}

ConnectionInfo UserInfo::get_connection_info()
{
	return this->connection_info;
}

AdminInfo::AdminInfo(unsigned long long admin_id, QString admin_name, ConnectionInfo connection_info, QString post_info, QString work_status)
{
	this->admin_id = admin_id;
	this->admin_name = admin_name;
	this->connection_info = connection_info;
	this->post_info = post_info;
	this->work_status = work_status;
}

AdminInfo::AdminInfo()
{
	this->admin_id = 0;
	this->admin_name = "";
	this->connection_info = ConnectionInfo();
}

unsigned long long AdminInfo::get_admin_id()
{
	return this->admin_id;
}

QString AdminInfo::get_admin_name()
{
	return this->admin_name;
}

ConnectionInfo AdminInfo::get_connection_info()
{
	return this->connection_info;
}

QString AdminInfo::get_post_info()
{
	return this->post_info;
}

QString AdminInfo::get_work_status()
{
	return this->work_status;
}

void AdminInfo::set_admin_name(QString admin_name)
{
	this->admin_name = admin_name;
}

void AdminInfo::set_connection_info(ConnectionInfo connection_info)
{
	this->connection_info = connection_info;
}

void AdminInfo::set_post_info(QString post_info)
{
	this->post_info = post_info;
}

void AdminInfo::set_work_status(QString work_status)
{
	this->work_status = work_status;
}

void AdminInfo::change_admin_info(QString admin_name, ConnectionInfo connection_info)
{
	this->admin_name = admin_name;
	this->connection_info = connection_info;
}

void AdminInfo::change_admin_info(AdminInfo admin_info)
{
	this->admin_name = admin_info.get_admin_name();
	this->connection_info = admin_info.get_connection_info();
}
