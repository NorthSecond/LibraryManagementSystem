#pragma once

#include <QString>

namespace LibraryBookInfo {
    // 图书状态
    enum bookStatus{
        onShelf,
        Borrowed,
        Wartung,
        others
    };

    // 出版社信息
    class PressInfo{
    private:
        QString name;

    };

    // 作者信息
    class AuthorInfo{
    private:
        QString name;
    };

    // 图书信息
    class Book{
    private:
        QString ISBN;
        QString book_name;
        PressInfo press;
        AuthorInfo auth;
        QString language_info;
        QString version;
        QString brief;
    public:
        Book(QString ISBN, QString book_name, PressInfo press, AuthorInfo auth, QString lang_info = "", QString ver = "", QString brief = "");
        Book(QString ISBN, QString book_name, unsigned long long press_id, unsigned long long auth_id, QString lang_info = "", QString ver = "", QString brief = "");
        QString get_ISBN();
        QString get_book_name();
        unsigned long long get_press_id();
        unsigned long long get_author_id();
        QString get_language_info();
        QString get_book_version();
        QString get_book_brief();
    };
}

class BookInfo
{
    unsigned long long book_index;
    LibraryBookInfo::Book book;
    LibraryBookInfo::bookStatus status;
public:
    BookInfo(LibraryBookInfo::Book book);
    BookInfo(QString ISBN);
    LibraryBookInfo::Book get_book();
};

class BookInfoBrief 
{
    unsigned long long book_index;
    QString ISBN;
	QString book_name;
    LibraryBookInfo::bookStatus status;

public:
	BookInfoBrief(unsigned long long book_index, QString ISBN, QString book_name, LibraryBookInfo::bookStatus status);
	BookInfoBrief(QString ISBN);
	unsigned long long get_book_index();
	QString get_ISBN();
	QString get_book_name();
	LibraryBookInfo::bookStatus get_book_status();
};
