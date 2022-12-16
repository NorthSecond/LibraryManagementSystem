#include "bookinfo.h"

LibraryBookInfo::Book::Book(QString ISBN, QString book_name, PressInfo press, AuthorInfo auth, QString lang_info, QString ver, QString brief):ISBN(ISBN), book_name(book_name), press(press), auth(auth), language_info(lang_info), version(ver), brief(brief){}

BookInfo::BookInfo(LibraryBookInfo::Book book)
    : book(book)
{
    this->status = LibraryBookInfo::bookStatus::onShelf;

}

//BookInfo::BookInfo(QString ISBN){
//    this->book = db.get_book_from_ISBN();

//    LibraryBookInfo::bookStatus::onShelf;

//}
