#pragma once

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVector>

#include "userinfo.h"
#include "bookinfo.h"
#include "connectioninfo.h"
#include "punishinfo.h"

class DatabaseRepository
{
private:
    QSqlDatabase db;
    void initializeDatabase(QString hostName, int port, QString databaseName, QString userName, QString password);

public:
    DatabaseRepository();
    DatabaseRepository(QString host_name, int port, QString database_name, QString user_name, QString password);

    unsigned long long login(QString user_name, QString passwd, User::Role role);
    unsigned long long user_register(QString user_name, QString passwd, User::Role role);

	AdminInfo get_admin_info(unsigned long long admin_id);
	ConnectionInfo get_connection_info(unsigned long long user_id);
	bool change_admin_passwd(unsigned long long admin_id, QString new_passwd);
    bool update_admin_info(AdminInfo info);

	QVector<UserInfo> get_user_list();
	bool add_user(UserInfo info);
	UserInfo get_user(unsigned long long user_id);
	bool update_user(UserInfo info);
	bool delete_user(unsigned long long user_id);

    
    unsigned long long addBookInfo(LibraryBookInfo::Book book);
    unsigned long long addBook(LibraryBookInfo::Book book, LibraryBookInfo::bookStatus status);
    bool changeBookStatus(unsigned long long book_index, LibraryBookInfo::bookStatus status);
    bool deleteBook(unsigned long long book_index);
    

    unsigned long long  borrow_book(unsigned long long user_id, unsigned long long book_index, unsigned long long admin_id = 0);
    unsigned long long return_book(unsigned long long book_id);

	QVector<PunishInfo> get_punish_info(unsigned long long uid);
    bool punish(unsigned long long id, unsigned long long user_id);
    
    ~DatabaseRepository();
};

extern DatabaseRepository* db_repo;
