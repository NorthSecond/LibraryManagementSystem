#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QMessageBox>
#include <QButtonGroup>

#include "bookinfo.h"
#include "databaseRepository.h"
#include "userinfo.h"

namespace Ui {
class BookManagementDialog;
}

class BookManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookManagementDialog(QWidget *parent = nullptr);
    ~BookManagementDialog();

private:
    Ui::BookManagementDialog *ui;
	AdminInfo admin_info;
	QVector<BookInfo> infos;
	LibraryBookInfo::Book now_book;
	QStandardItemModel* mod;
	QButtonGroup* btnGroup;

public slots:
	void getAdminInfo(AdminInfo info);

private slots:
	void on_mod_selected();
	void on_search_btn_clicked();
	void on_add_book_btn_clicked();
	void on_add_book_info_btn_clicked();
	void on_modify_book_btn_clicked();
	void on_modify_book_info_btn_clicked();
	void on_delete_book_btn_clicked();
	void on_back_btn_clicked();
};

