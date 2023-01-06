#pragma once

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDatetime>
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
	bool change_user_pwd(unsigned long long user_id, QString new_passwd);

	QVector<BookInfoBrief> searchBookBrief(unsigned long long book_id);
    
	LibraryBookInfo::PressInfo get_press_by_id(unsigned long long press_id);
	LibraryBookInfo::AuthorInfo get_auth_by_id(unsigned long long author_id);
	LibraryBookInfo::Book get_book_by_ISBN(QString ISBN);
	QVector<BookInfo> get_books_by_ISBN(QString ISBN);
	QVector<BookInfo> get_books_by_name(QString book_name);
    
	BookInfo get_book_by_index(unsigned long long book_index);
    bool addBookInfo(LibraryBookInfo::Book book);
    unsigned long long addBook(LibraryBookInfo::Book book, LibraryBookInfo::bookStatus status);
    bool deleteBook(unsigned long long book_index);
	bool modifyBook(unsigned long long book_index, LibraryBookInfo::bookStatus status);
	unsigned long long add_author_info(LibraryBookInfo::AuthorInfo info);
	unsigned long long add_press_info(LibraryBookInfo::PressInfo info); 
	bool update_book_info(QString ISBN, LibraryBookInfo::Book book);
    
	bool is_user_limited(unsigned long long user_id);
    bool borrow_book(unsigned long long user_id, unsigned long long book_index);
    bool rtn_book(unsigned long long book_id);
    bool break_book(unsigned long long book_id);

	QVector<PunishInfo> get_punish_info(unsigned long long uid);
    bool punish(unsigned long long id, unsigned long long user_id);
    
    ~DatabaseRepository();
};

extern DatabaseRepository* db_repo;
