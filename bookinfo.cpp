#include "bookinfo.h"


LibraryBookInfo::PressInfo::PressInfo()
{
	this->press_id = 0;
}

LibraryBookInfo::PressInfo::PressInfo(unsigned long long press_id, QString name)
{
	this->press_id = press_id;
	this->name = name;
}

unsigned long long LibraryBookInfo::PressInfo::get_press_id()
{
	return press_id;
}

QString LibraryBookInfo::PressInfo::get_name()
{
	return name;
}

void LibraryBookInfo::PressInfo::set_name(QString name)
{
	this->name = name;
}

/*************** AuthorInfo *****************/

LibraryBookInfo::AuthorInfo::AuthorInfo()
{
	this->author_id = 0;
}

LibraryBookInfo::AuthorInfo::AuthorInfo(unsigned long long author_id, QString name)
{
	this->author_id = author_id;
	this->name = name;
}

unsigned long long LibraryBookInfo::AuthorInfo::get_author_id()
{
	return author_id;
}

QString LibraryBookInfo::AuthorInfo::get_name()
{
	return name;
}

void LibraryBookInfo::AuthorInfo::set_name(QString name)
{
	this->name = name;
}

/********************* Book ************************/

LibraryBookInfo::Book::Book(QString ISBN, QString book_name, PressInfo press, AuthorInfo auth, QString lang_info, QString ver, QString brief) :ISBN(ISBN), book_name(book_name), press(press), auth(auth), language_info(lang_info), version(ver), brief(brief) {}

//LibraryBookInfo::Book::Book(QString ISBN, QString book_name, unsigned long long press_id, unsigned long long auth_id, QString lang_info, QString ver, QString brief)
//{
//	this->ISBN = ISBN;
//	this->book_name = book_name;
//	this->press = db_repo->get_press_by_id(press_id);
//	this->auth = db_repo->get_auth_by_id(auth_id);
//	this->language_info = lang_info;
//	this->version = ver;
//	this->brief = brief;
//}

LibraryBookInfo::Book::Book()
{
	this->ISBN = "";
}

QString LibraryBookInfo::Book::get_ISBN()
{
	return this->ISBN;
}

QString LibraryBookInfo::Book::get_book_name()
{
	return this->book_name;
}

unsigned long long LibraryBookInfo::Book::get_press_id()
{
	return this->press.get_press_id();
}

unsigned long long LibraryBookInfo::Book::get_author_id()
{
	return this->auth.get_author_id();
}

QString LibraryBookInfo::Book::get_author_name()
{
	return this->auth.get_name();
}

QString LibraryBookInfo::Book::get_press_name()
{
	return this->press.get_name();
}

QString LibraryBookInfo::Book::get_language_info()
{
	return this->language_info;
}

QString LibraryBookInfo::Book::get_book_version()
{
	return this->version;
}

QString LibraryBookInfo::Book::get_book_brief()
{
	return this->brief;
}

/********************* BookInfo ****************************/

BookInfo::BookInfo(unsigned long long book_index, LibraryBookInfo::Book book, LibraryBookInfo::bookStatus status)
	: book_index(book_index), book(book), status(status) {
}


BookInfo::BookInfo(LibraryBookInfo::Book book)
	: book(book)
{
	this->status = LibraryBookInfo::bookStatus::onShelf;

}

//BookInfo::BookInfo(QString ISBN)
//{
//	this->book = db_repo->get_book_by_ISBN(ISBN);
//	this->status = LibraryBookInfo::bookStatus::onShelf;
//}

LibraryBookInfo::Book BookInfo::get_book()
{
	return this->book;
}

unsigned long long BookInfo::get_book_index()
{
	return this->book_index;
}

LibraryBookInfo::bookStatus BookInfo::get_book_status()
{
	return this->status;
}

/*************************** BookInfoBrief ***************************/

BookInfoBrief::BookInfoBrief(unsigned long long book_index, QString ISBN, QString book_name, LibraryBookInfo::bookStatus status)
	: book_index(book_index), ISBN(ISBN), book_name(book_name), status(status)
{

}

BookInfoBrief::BookInfoBrief(QString ISBN)
	: ISBN(ISBN)
{

}

unsigned long long BookInfoBrief::get_book_index()
{
	return book_index;
}

QString BookInfoBrief::get_ISBN()
{
	return ISBN;
}

QString BookInfoBrief::get_book_name()
{
	return book_name;
}

LibraryBookInfo::bookStatus BookInfoBrief::get_book_status()
{
	return status;
}

