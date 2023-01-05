#include "bookinfo.h"

LibraryBookInfo::Book::Book(QString ISBN, QString book_name, PressInfo press, AuthorInfo auth, QString lang_info, QString ver, QString brief) :ISBN(ISBN), book_name(book_name), press(press), auth(auth), language_info(lang_info), version(ver), brief(brief) {}

BookInfo::BookInfo(LibraryBookInfo::Book book)
	: book(book)
{
	this->status = LibraryBookInfo::bookStatus::onShelf;

}

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

