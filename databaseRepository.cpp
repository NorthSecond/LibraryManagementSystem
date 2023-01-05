#include "databaseRepository.h"

DatabaseRepository::DatabaseRepository()
{
	QString hostName = "127.0.0.1";
	int port = 3306;
	QString databaseName = "lib_idx";
	QString userName = "root";
	QString password = "357480";
	initializeDatabase(hostName, port, databaseName, userName, password);
}

DatabaseRepository::DatabaseRepository(QString host_name, int port, QString database_name, QString user_name, QString password) {
	initializeDatabase(host_name, port, database_name, user_name, password);
}

void DatabaseRepository::initializeDatabase(QString hostName, int port, QString databaseName, QString userName, QString password) {
	db = QSqlDatabase::addDatabase("QODBC");
	db.setHostName(hostName);
	db.setPort(port);
	QString connectString = QStringLiteral(
		"DRIVER={MySQL ODBC 8.0 Unicode Driver};"
		"SERVER=%1:%2;"
		"DATABASE=%3;"
		"UID=%4;"
		"PWD=%5;").arg(hostName).arg(port).arg(databaseName).arg(userName).arg(password);
	db.setDatabaseName(connectString);
	db.setUserName(userName);
	db.setPassword(password);
	if (!db.open())
	{// fail to open database
		QMessageBox::critical(NULL, "Error", "Database connection failed!");
		exit(2);
	}
}

DatabaseRepository::~DatabaseRepository() {
	db.close();
}

unsigned long long DatabaseRepository::login(QString user_name, QString passwd, User::Role role) {
	int role_int = static_cast<int>(role);

	QString query;

	switch (role) {
	case User::ADMIN:
		query = "SELECT * FROM admininfo WHERE admin_name = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\'";
		break;
	case User::STUDENT:
	case User::TEACHER:
	case User::OUTCOME:
		query = "SELECT * FROM reader_info WHERE reader_id = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\' AND reader_type = " +
			QString::fromStdString(std::to_string(role_int));
		break;
	}

	// query the sql sentence
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}
	else {
		return 0;
	}
}

unsigned long long DatabaseRepository::user_register (QString user_name, QString passwd, User::Role role)
{
    QString query = "";
    unsigned int user_role = 0;
    switch(role){
    case User::STUDENT:
        user_role = 0;
        break;
    case User::TEACHER:
        user_role = 1;
        break;
    case User::ADMIN :
        user_role = 2;
        break;
    case User::OUTCOME:
        user_role = 3;
        break;
    }

	query = "INSERT INTO  (user_name, passwd, user_role) VALUES ('" + user_name + "', '" + passwd + "', " + QString::number(user_role) + ");";
	return 0;
}

AdminInfo DatabaseRepository::get_admin_info(unsigned long long admin_id) {
	QString query = "SELECT * FROM admininfo WHERE admin_id = " + QString::number(admin_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		unsigned long long connection_id = sql_query.value(3).toULongLong();
		ConnectionInfo connection_info = get_connection_info(connection_id);
		return AdminInfo(sql_query.value(0).toULongLong(), sql_query.value(2).toString(), 
			connection_info, sql_query.value(4).toString(), sql_query.value(5).toString());
	}
	else {
		return AdminInfo();
	}
}

ConnectionInfo DatabaseRepository::get_connection_info(unsigned long long user_id)
{
	QString query = "SELECT * FROM connection_info WHERE id = " + QString::number(user_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		return ConnectionInfo(sql_query.value(0).toULongLong(), sql_query.value(1).toString(), 
			sql_query.value(2).toString(), sql_query.value(3).toString(), sql_query.value(4).toString());
	}
	else {
		return ConnectionInfo();
	}
}

bool DatabaseRepository::change_admin_passwd(unsigned long long admin_id, QString new_passwd)
{
	QString query = "UPDATE admininfo SET passwd = \'" + new_passwd + "\' WHERE admin_id = " + QString::number(admin_id);
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

bool DatabaseRepository::update_admin_info(AdminInfo info)
{
	QString query = "UPDATE connection_info SET telephone = \' " + info.get_connection_info().get_telephone()
		+ "\' WHERE id = " + QString::number(info.get_connection_info().get_connection_id());
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

QVector<UserInfo> DatabaseRepository::get_user_list()
{
	QString query = "SELECT * FROM reader_info";
	QSqlQuery sql_query;
	sql_query.exec(query);
	QVector<UserInfo> user_list;
	while (sql_query.next()) {
		unsigned long long connection_id = sql_query.value(3).toULongLong();
		ConnectionInfo connection_info = get_connection_info(connection_id);
		User::Role role;
		if (sql_query.value(4) == "学生") {
			role == User::STUDENT;
		}
		else if (sql_query.value(4) == "教师") {
			role = User::TEACHER;
		}
		else if (sql_query.value(4) == "外来") {
			role = User::OUTCOME;
		}
		User::Status status;
		if (sql_query.value(5) == "正常") {
			status = User::Normal;
		}
		else {
			status = User::Banned;
		}
		user_list.push_back(UserInfo(sql_query.value(0).toULongLong(), sql_query.value(2).toString(), role, status, connection_info));
	}
	return user_list;
}

bool DatabaseRepository::add_user(UserInfo info) 
{
	ConnectionInfo connection_info = info.get_connection_info();
	// insert connect first
	QString sql = "INSERT INTO connection_info (telephone) VALUES (\'" + connection_info.get_telephone() +  "\')";
	QSqlQuery sql_query;
	if (!sql_query.exec(sql)) {
		return false;
	}
	
	sql = "SELECT id FROM connection_info WHERE telephone = \'" + connection_info.get_telephone() + "\'";
	if (!sql_query.exec(sql)) {
		return false;
	}
	unsigned long long conn_id;
	while (sql_query.next())
	{
		conn_id = sql_query.value(0).toULongLong();
	}
	
	QString status = info.get_user_status() == User::Normal ? "正常" : "禁用";
	QString role = info.get_user_role() == User::TEACHER ? "教师" : info.get_user_role() == User::STUDENT ? "学生" : "外来";
	// insert account
	sql = "INSERT INTO reader_info (passwd, reader_name, connect_info, reader_type, reader_status, borrowed_num) VALUES (\'\', \'"
		+ info.get_user_name() + "\', " + QString::number(conn_id) + ", \'" + role + "\', \'" + status + "\', 0)";
	return sql_query.exec(sql);
}

UserInfo DatabaseRepository::get_user(unsigned long long user_id) 
{
	QString query = "SELECT * FROM reader_info WHERE reader_id = " + QString::number(user_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	UserInfo res;
	if (sql_query.next()) {
		unsigned long long connection_id = sql_query.value(3).toULongLong();
		ConnectionInfo connection_info = get_connection_info(connection_id);
		User::Role role;
		if (sql_query.value(4) == "学生") {
			role == User::STUDENT;
		}
		else if (sql_query.value(4) == "教师") {
			role = User::TEACHER;
		}
		else if (sql_query.value(4) == "外来") {
			role = User::OUTCOME;
		}
		User::Status status;
		if (sql_query.value(5) == "正常") {
			status = User::Normal;
		}
		else {
			status = User::Banned;
		}
		res = UserInfo(sql_query.value(0).toULongLong(), sql_query.value(2).toString(), role, status, connection_info);
	}
	return res;
}

bool DatabaseRepository::update_user(UserInfo info) {
	ConnectionInfo conn = info.get_connection_info();
	QString query = "UPDATE connection_info SET telephone = \' " + info.get_connection_info().get_telephone()
		+ "\' WHERE id = " + QString::number(info.get_connection_info().get_connection_id());
	QSqlQuery sql_query;
	if (!sql_query.exec(query)) {
		return false;
	}
	query = "UPDATE reader_info SET reader_name = \'" + info.get_user_name() + "\', reader_type = \'" +
		(info.get_user_role() == User::TEACHER ? "教师" : info.get_user_role() == User::STUDENT ? "学生" : "外来") + "\', reader_status = \'" +
		(info.get_user_status() == User::Normal ? "正常" : "禁用") + "\' WHERE reader_id = " + QString::number(info.get_user_id());
	return sql_query.exec(query);
}

bool DatabaseRepository::delete_user(unsigned long long user_id)
{
	QString sql = "DELETE FROM reader_info WHERE reader_id = " + QString::number(user_id);
	QSqlQuery sql_query;
	return sql_query.exec(sql);
}

bool check_username_usable(QString user_name){
    QString query = "SELECT user_id FROM user WHERE user_name = '" + user_name + "';";
    QSqlQuery sql_query;

    sql_query.prepare(query);
    if(!sql_query.exec()){
        QMessageBox::critical(NULL, "Error", "Database operation Failed !");
        exit(2);
    }
    if(sql_query.next()){
        return false;
    }
    return true;
}

unsigned long long DatabaseRepository::borrow_book(unsigned long long user_id, unsigned long long book_index, unsigned long long admin_id){
	return 0;
}

unsigned long long DatabaseRepository::return_book(unsigned long long book_id){
	return 0;
}

//LibraryBookInfo::Book find_book_from_ISBN(QString ISBN){
//    QString query = "SELECT * FROM book WHERE ISBN = '" + ISBN + "';";
//    QSqlQuery sql_query;
//    sql_query.prepare(query);
//    if(!sql_query.exec()){
//        QMessageBox::critical(NULL, "Error", "Database operation Failed !");
//        exit(2);
//    }
//    sql_query.next();
//    LibraryBookInfo::Book book(sql_query.value(0), sql_query.value(1), sql_query.value(2).toULongLong(), sql_query.value(3).toLongLong(), sql_query.value(4), sql_query.value(5));
//    return book;
//}

//bool insert_book_info(LibraryBookInfo::Book book){
//    QString query = "INSERT INTO `book_info` (ISBN, book_name, press_id, author_id, language_info, version, brief) VALUES ('" + book.get_ISBN() + "', '" + book.get_book_name() + "', " + QString::number(book.get_press_id()) + ", " + QString::number(book.get_author_id()) + ", '" + book.get_language_info() + "', '" + book.get_book_version()
// + "', '" + book.get_book_brief() ;
//// "INSERT INTO book (ISBN, book_name, author, publisher, publish_date, price, book_index, book_status) VALUES ('" + book.ISBN + "', '" + book.book_name + "', '" + book.author + "', '" + book.publisher + "', '" + book.publish_date + "', " + QString::number(book.price) + ", " + QString::number(book.book_index) + ", " + QString::number(book.book_status) + ");";
//    QSqlQuery sql_query;
//    sql_query.prepare(query);
//    return sql_query.exec();
//}

//bool get_book_numbers(LibraryBookInfo::Book book){
//    QString book_ISBN = book.get_ISBN();
//    QString query = "SELECT num(*) from `book` where `ISBN` = " + book.get_ISBN();
//    QSqlQuery sql_query;
//    sql_query.prepare(query);
//    if(!sql_query.exec()){
//        QMessageBox::critical(NULL, "Error", "Database operation Failed !");
//        exit(2);
//    }
//    return sql_query.next();
//}

//bool insert_book(BookInfo book_info)
//{
//    LibraryBookInfo::Book book = book_info.get_book();
//    //QString query = "INSERT INTO book (ISBN, book_name, author, publisher, publish_date, price, book_index, book_status) VALUES ('" + book.ISBN + "', '" + book.book_name + "', '" + book.author + "', '" + book.publisher + "', '" + book.publish_date + "', " + QString::number(book.price) + ", " + QString::number(book.book_index) + ", " + QString::number(book.book_status) + ");";

//    QSqlQuery sql_query;
//    sql_query.prepare(query);
//    return sql_query.exec();
//}

//User::Status get_user_status(QString user_name){
//    QString query = "SELECT status FROM user WHERE user_name = '" + user_name + "';";
//    QSqlQuery sql_query;
//    sql_query.prepare(query);
//    if(!sql_query.exec()){
//        QMessageBox::critical(NULL, "Error", "Database operation Failed !");
//        exit(2);
//    }
//    sql_query.next();
//    return (User::Status)sql_query.value(0).toUInt();
//}

QVector<PunishInfo> DatabaseRepository::get_punish_info(unsigned long long user_id)
{
	QVector<PunishInfo> res;
	QString query = "SELECT * FROM violate_info WHERE reader_id = " + QString::number(user_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	while (sql_query.next()) {
		res.push_back(PunishInfo(sql_query.value(0).toULongLong(), sql_query.value(1).toULongLong(), sql_query.value(2).toULongLong(),
			sql_query.value(3).toDateTime(), sql_query.value(4).toInt(), sql_query.value(5).toInt()));
	}
	
	return res;
}

bool DatabaseRepository::punish(unsigned long long id, unsigned long long user_id)
{
	// 使用事务同步更新状态
	if (QSqlDatabase::database().transaction()) //启动事务操作
	{
		QSqlQuery query;
		query.exec("UPDATE violate_info SET status = 1 WHERE id = " + QString::number(id));
		query.exec("UPDATE reader_info SET reader_status = \'正常\' where reader_id = " + QString::number(user_id));
		if (!QSqlDatabase::database().commit())
		{
			if (!QSqlDatabase::database().rollback()) {
				return false;
			}
		}
	}
	return true;
}

//void flush_all_status(){

//}

//unsigned int can_borrow_num(QString user_name){

//}

//bool change_user_info(unsigned long long user_id, UserInfo user_info){
////    QString query = "UPDATE `user_info` SET `user_name` = '" + user_info.get_user_name() + "', `user_password` = '" + user_info.get_user_password() + "', `user_email` = '" + user_info.get_user_email() + "', `user_phone` = '" + user_info.get_user_phone() + "', `user_address` = '" + user_info.get_user_address() + "', `user_status` = " + QString::number(user_info.get_user_status()) + " WHERE `user_id` = " + QString::number(user_id) + ";";

//    QSqlQuery sql_query;
////    sql_query.prepare(query);
//    return sql_query.exec();
//}



// global variable
DatabaseRepository* db_repo = new DatabaseRepository();