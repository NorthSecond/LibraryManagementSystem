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

	QString query;

	switch (role) {
	case User::ADMIN:
		query = "SELECT * FROM admininfo WHERE admin_name = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\'";
		break;
	case User::STUDENT:
		query = "SELECT * FROM reader_info WHERE reader_name = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\'" + " AND reader_type = \'学生\'";
		break;
	case User::TEACHER:
		query = "SELECT * FROM reader_info WHERE reader_name = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\'" + " AND reader_type = \'教师\'";
		break;
	case User::OUTCOME:
		query = "SELECT * FROM reader_info WHERE reader_name = \'" + user_name
			+ "\' AND passwd = \'" + passwd + "\'" + " AND reader_type = \'外来\'";
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

unsigned long long DatabaseRepository::user_register(QString user_name, QString passwd, User::Role role)
{
	QString query = "";
	unsigned int user_role = 0;
	switch (role) {
	case User::STUDENT:
		user_role = 0;
		break;
	case User::TEACHER:
		user_role = 1;
		break;
	case User::ADMIN:
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
			role = User::STUDENT;
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
		user_list.push_back(UserInfo(sql_query.value(0).toULongLong(), sql_query.value(2).toString(), role, status, connection_info, sql_query.value(6).toULongLong()));
	}
	return user_list;
}

bool DatabaseRepository::add_user(UserInfo info)
{
	ConnectionInfo connection_info = info.get_connection_info();
	// insert connect first
	QString sql = "INSERT INTO connection_info (telephone) VALUES (\'" + connection_info.get_telephone() + "\')";
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
	sql = "INSERT INTO reader_info (passwd, reader_name, connect_info, reader_type, reader_status, borrowed_num) VALUES (\'123456\', \'"
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
			role = User::STUDENT;
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
		res = UserInfo(sql_query.value(0).toULongLong(), sql_query.value(2).toString(), role, status, connection_info, sql_query.value(6).toULongLong());
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

QVector<BookInfoBrief> DatabaseRepository::searchBookBrief(unsigned long long book_id)
{
	// natural join to find the book_name
	QVector<BookInfoBrief> res;
	QString query = "SELECT book_index, book_ISBN, book_name, book_status FROM book_info as bi INNER JOIN book as b ON bi.book_ISBN = b.ISBN WHERE bi.book_index = " + QString::number(book_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	while (sql_query.next()) {
		LibraryBookInfo::bookStatus status;
		if (sql_query.value(3).toString() == "在架上") {
			status = LibraryBookInfo::onShelf;
		}
		else if (sql_query.value(3).toString() == "借出") {
			status = LibraryBookInfo::Borrowed;
		}
		else {
			status = LibraryBookInfo::Wartung;
		}
		res.push_back(BookInfoBrief(sql_query.value(0).toULongLong(), sql_query.value(1).toString(), sql_query.value(2).toString(), status));
	}
	return res;
}

LibraryBookInfo::PressInfo DatabaseRepository::get_press_by_id(unsigned long long press_id)
{
	LibraryBookInfo::PressInfo res;
	QString query = "SELECT * FROM press_info WHERE press_index = " + QString::number(press_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		res = LibraryBookInfo::PressInfo(sql_query.value(0).toULongLong(), sql_query.value(1).toString());
	}
	return res;
}

LibraryBookInfo::AuthorInfo DatabaseRepository::get_auth_by_id(unsigned long long author_id) {
	LibraryBookInfo::AuthorInfo auth;
	QString query = "SELECT * FROM author_info WHERE author_index = " + QString::number(author_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		auth = LibraryBookInfo::AuthorInfo(sql_query.value(0).toULongLong(), sql_query.value(1).toString());
	}
	return auth;
}

LibraryBookInfo::Book DatabaseRepository::get_book_by_ISBN(QString ISBN) {
	LibraryBookInfo::Book res;
	QString query = "SELECT * FROM book WHERE ISBN = \'" + ISBN + "\'";
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		LibraryBookInfo::PressInfo press = get_press_by_id(sql_query.value(2).toULongLong());
		LibraryBookInfo::AuthorInfo author = get_auth_by_id(sql_query.value(3).toULongLong());
		res = LibraryBookInfo::Book(ISBN, sql_query.value(1).toString(), press, author,
			sql_query.value(4).toString(), sql_query.value(5).toString(), sql_query.value(6).toString());
	}
	return res;
}

QVector<BookInfo> DatabaseRepository::get_books_by_ISBN(QString ISBN)
{
	QVector<BookInfo> res;
	QString query = "SELECT book_index, book_ISBN, book_status, book_name, publish_info, author_info, language_info,"
		" book_version, brief_intro FROM book_info INNER JOIN book ON book_info.book_ISBN = book.ISBN WHERE book_ISBN = \'" + ISBN + "\'";

	QSqlQuery sql_query;
	sql_query.exec(query);
	while (sql_query.next())
	{
		LibraryBookInfo::bookStatus status;
		if (sql_query.value(2).toString() == "在架上") {
			status = LibraryBookInfo::onShelf;
		}
		else if (sql_query.value(2).toString() == "借出") {
			status = LibraryBookInfo::Borrowed;
		}
		else {
			status = LibraryBookInfo::Wartung;
		}
		LibraryBookInfo::PressInfo press = get_press_by_id(sql_query.value(4).toULongLong());
		LibraryBookInfo::AuthorInfo author = get_auth_by_id(sql_query.value(5).toULongLong());

		LibraryBookInfo::Book book = LibraryBookInfo::Book(sql_query.value(1).toString(), sql_query.value(3).toString(), press, author,
			sql_query.value(6).toString(), sql_query.value(7).toString(), sql_query.value(8).toString());

		res.push_back(BookInfo(sql_query.value(0).toULongLong(), book, status));
	}

	return res;
}

QVector<BookInfo> DatabaseRepository::get_books_by_name(QString book_name)
{
	QVector<BookInfo> res;
	QString query = "SELECT book_index, book_ISBN, book_status, book_name, publish_info, author_info, language_info,"
		" book_version, brief_intro FROM book_info INNER JOIN book ON book_info.book_ISBN = book.ISBN WHERE book_name = \'" + book_name + "\'";
	QSqlQuery sql_query;
	sql_query.exec(query);
	while (sql_query.next())
	{
		LibraryBookInfo::bookStatus status;
		if (sql_query.value(2).toString() == "在架上") {
			status = LibraryBookInfo::onShelf;
		}
		else if (sql_query.value(2).toString() == "借出") {
			status = LibraryBookInfo::Borrowed;
		}
		else {
			status = LibraryBookInfo::Wartung;
		}
		LibraryBookInfo::PressInfo press = get_press_by_id(sql_query.value(4).toULongLong());
		LibraryBookInfo::AuthorInfo author = get_auth_by_id(sql_query.value(5).toULongLong());

		LibraryBookInfo::Book book = LibraryBookInfo::Book(sql_query.value(1).toString(), sql_query.value(3).toString(), press, author,
			sql_query.value(6).toString(), sql_query.value(7).toString(), sql_query.value(8).toString());

		res.push_back(BookInfo(sql_query.value(0).toULongLong(), book, status));
	}
	return res;
}

BookInfo DatabaseRepository::get_book_by_index(unsigned long long book_index)
{
	BookInfo res;
	QString query = "SELECT book_index, book_ISBN, book_status, book_name, publish_info, author_info, language_info,"
		" book_version, brief_intro FROM book_info INNER JOIN book ON book_info.book_ISBN = book.ISBN WHERE book_index = " + QString::number(book_index);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next())
	{
		LibraryBookInfo::bookStatus status;
		if (sql_query.value(2).toString() == "在架上") {
			status = LibraryBookInfo::onShelf;
		}
		else if (sql_query.value(2).toString() == "借出") {
			status = LibraryBookInfo::Borrowed;
		}
		else {
			status = LibraryBookInfo::Wartung;
		}
		LibraryBookInfo::PressInfo press = get_press_by_id(sql_query.value(4).toULongLong());
		LibraryBookInfo::AuthorInfo author = get_auth_by_id(sql_query.value(5).toULongLong());

		LibraryBookInfo::Book book = LibraryBookInfo::Book(sql_query.value(1).toString(), sql_query.value(3).toString(), press, author,
			sql_query.value(6).toString(), sql_query.value(7).toString(), sql_query.value(8).toString());

		res = BookInfo(sql_query.value(0).toULongLong(), book, status);
	}
	return res;
}

bool DatabaseRepository::addBookInfo(LibraryBookInfo::Book book)
{
	QString query = "INSERT INTO book (ISBN, book_name, publish_info, author_info, language_info, book_version, brief_intro) VALUES (\'"
		+ book.get_ISBN() + "\', \'" + book.get_book_name() + "\', " + QString::number(book.get_press_id()) + ", " + QString::number(book.get_author_id()) +
		", \'" + book.get_language_info() + "\', \'" + book.get_book_version() + "\', \'" + book.get_book_brief() + "\')";
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

unsigned long long DatabaseRepository::addBook(LibraryBookInfo::Book book, LibraryBookInfo::bookStatus status)
{
	QString status_str = status == LibraryBookInfo::onShelf ? "在架上" :
		status == LibraryBookInfo::Borrowed ? "借出" : "损毁";
	QString query = "INSERT INTO book_info (book_ISBN, book_status) VALUES (\'"
		+ book.get_ISBN() + "\', \'" + status_str + "\')";
	QSqlQuery sql_query;
	if (!sql_query.exec(query)) {
		return 0;
	}
	query = "SELECT book_index FROM book_info WHERE book_ISBN = \'" + book.get_ISBN() + "\'";
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}
	return 0;
}

bool DatabaseRepository::deleteBook(unsigned long long book_index)
{
	QString query = "DELETE FROM book_info WHERE book_index = " + QString::number(book_index);
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

bool DatabaseRepository::modifyBook(unsigned long long book_index, LibraryBookInfo::bookStatus status)
{
	QString status_str = status == LibraryBookInfo::onShelf ? "在架上" :
		status == LibraryBookInfo::Borrowed ? "借出" : "损毁";
	QString query = "UPDATE book_info SET book_status = \'" + status_str + "\' WHERE book_index = " + QString::number(book_index);
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

unsigned long long DatabaseRepository::add_author_info(LibraryBookInfo::AuthorInfo info)
{
	// 先判断是否已经存在
	QString query = "SELECT author_index FROM author_info WHERE author_name = \'" + info.get_name() + "\'";
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}
	query = "INSERT INTO author_info author_name VALUES (\'" + info.get_name() + "\')";
	sql_query.exec(query);
	query = "SELECT author_index FROM author_info WHERE author_name = \'" + info.get_name() + "\'";
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}
	return 0;
}

unsigned long long DatabaseRepository::add_press_info(LibraryBookInfo::PressInfo info)
{
	// 先判断是否已经存在
	QString query = "SELECT press_index FROM press_info WHERE press_name = \'" + info.get_name() + "\'";
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}

	query = "INSERT INTO press_info press_name VALUES (\'" + info.get_name() + "\')";
	sql_query.exec(query);
	query = "SELECT press_index FROM press_info WHERE press_name = \'" + info.get_name() + "\'";
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong();
	}
	return 0;
}

bool DatabaseRepository::update_book_info(QString ISBN, LibraryBookInfo::Book book)
{
	QString query = "UPDATE book SET book_name = \'" + book.get_book_name() + "\', publish_info = " + QString::number(book.get_press_id()) + ", author_info = " + QString::number(book.get_author_id()) +
		", language_info = \'" + book.get_language_info() + "\', book_version = \'" + book.get_book_version() + "\', brief_intro = \'" + book.get_book_brief() + "\' WHERE ISBN = \'" + ISBN + "\'";
	QSqlQuery sql_query;
	return sql_query.exec(query);
}

bool check_username_usable(QString user_name) {
	QString query = "SELECT user_id FROM user WHERE user_name = '" + user_name + "';";
	QSqlQuery sql_query;

	sql_query.prepare(query);
	if (!sql_query.exec()) {
		QMessageBox::critical(NULL, "Error", "Database operation Failed !");
		exit(2);
	}
	if (sql_query.next()) {
		return false;
	}
	return true;
}

bool DatabaseRepository::is_user_limited(unsigned long long user_id)
{
	// INNER JOIN
	QString query = "SELECT borrowed_num, num_limit from reader_info as ri INNER JOIN reader_type as rt ON ri.reader_type = rt.typename WHERE reader_id = " + QString::number(user_id);
	QSqlQuery sql_query;
	sql_query.exec(query);
	if (sql_query.next()) {
		return sql_query.value(0).toULongLong() >= sql_query.value(1).toULongLong();
	}
}

bool DatabaseRepository::borrow_book(unsigned long long user_id, unsigned long long book_id) {
	QSqlDatabase::database().transaction();
	QSqlQuery query;
	QString sql1, sql2, sql3;
	sql1 = "UPDATE book_info SET book_status = \'借出\' WHERE book_index = " + QString::number(book_id) + ";";
	sql2 = "UPDATE reader_info SET borrowed_num = borrowed_num + 1 WHERE reader_id = " + QString::number(user_id) + ";";
	QDateTime now = QDateTime::currentDateTime();
	sql3 = "INSERT INTO lend_log (book_index, reader_id, lend_time) VALUES (" +
		QString::number(book_id) + ", " + QString::number(user_id) + ", \'" + now.toString("yyyy-MM-dd hh:mm:ss") + "\');";
	query.exec(sql1);
	// 用户借阅数量+1
	query.exec(sql2);
	// 写入借阅记录
	query.exec(sql3);
	
	return QSqlDatabase::database().commit();
}

bool DatabaseRepository::rtn_book(unsigned long long book_id) {
	// 使用事务同步更新状态
	if (QSqlDatabase::database().transaction()) //启动事务操作
	{
		QSqlQuery query;
		query.exec("UPDATE book_info SET book_status = \'在架上\' WHERE book_index = " + QString::number(book_id));
		// 找到借阅记录进行归还
		query.exec("SELECT id, reader_id into @log_id, @reader_id FROM lend_log WHERE book_index = " + QString::number(book_id) + "ORDER BY lend_time DESC LIMIT 1;");
		// 用户借阅数量-1
		query.exec("UPDATE reader_info SET borrowed_num = borrowed_num - 1 WHERE reader_id = @reader_id;");
		// 写入归还记录
		query.exec("INSERT INTO lend_return_info (lend_id, return_time) VALUES (@log_id, \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\');");
		// 判断是否超期
		query.exec("SELECT lend_time into @lend_time FROM lend_log WHERE id = @log_id;");
		query.exec("SELECT DATEDIFF(\'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\', @lend_time) into @diff");
		query.exec("SELECT time_limit into @tlimit FROM reader_type WHERE typename = (SELECT reader_type FROM reader_info WHERE reader_id = @reader_id);");
		query.exec("SELECT IF(@diff > @tlimit, 1, 0) into @is_overdue;");
		// 写入处罚记录
		query.exec("IF @is_overdue = 1 THEN INSERT INTO violate_info (book_index, reader_id, banned_time, type_id, status) VALUES (" +
			QString::number(book_id) + ", @reader_id, " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + ", 1, 0);");
		// 个人状态更新
		query.exec("IF @is_overdue = 1 THEN UPDATE reader_info SET reader_status = '受限' WHERE reader_id = @reader_id;");

		if (!QSqlDatabase::database().commit())
		{
			if (!QSqlDatabase::database().rollback()) {
				return false;
			}
		}
	}
}

bool DatabaseRepository::break_book(unsigned long long book_id) {
	// 使用事务同步更新状态
	if (QSqlDatabase::database().transaction()) //启动事务操作
	{
		QSqlQuery query;
		query.exec("UPDATE book_info SET book_status = '损毁' WHERE book_index = " + QString::number(book_id));
		// 找到借阅记录进行归还
		query.exec("SELECT id, reader_id into @log_id, @reader_id FROM lend_log WHERE book_index = " + QString::number(book_id) + 
			" ORDER BY lend_time DESC LIMIT 1;");
		// 用户借阅数量-1
		query.exec("UPDATE reader_info SET borrowed_num = borrowed_num - 1 WHERE reader_id = @reader_id;");
		// 写入惩罚记录
		query.exec("INSERT INTO violate_info(book_index, reader_id, banned_time, type_id, `status`) VALUES("
			+ QString::number(book_id) + ", @reader_id, \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\', 2, 0);");
		// 用户被限制
		query.exec("UPDATE reader_info SET reader_status = \'受限\' WHERE reader_id = @reader_id");
		if (!QSqlDatabase::database().commit())
		{
			if (!QSqlDatabase::database().rollback()) {
				return false;
			}
		}
	}
}

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
	if (db.transaction()) //启动事务操作
	{
		QSqlQuery query;
		query.exec("UPDATE violate_info SET `status` = 1 WHERE id = " + QString::number(id)) + ";";
		query.exec("UPDATE reader_info SET reader_status = \'正常\' where reader_id = " + QString::number(user_id)) + ";";
		query.clear();
		if (db.commit())
		{
			return true;
		}
		else {
			db.rollback();
			return false;
		}
	}
	return false;
}

// global variable
DatabaseRepository* db_repo = new DatabaseRepository();
