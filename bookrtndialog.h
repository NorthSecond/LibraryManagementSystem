#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QMessagebox>

#include "userinfo.h"
#include "databaseRepository.h"
#include "bookinfo.h"

namespace Ui {
class BookRtnDialog;
}

class BookRtnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookRtnDialog(QWidget *parent = nullptr);
    ~BookRtnDialog();
    

private:
    Ui::BookRtnDialog *ui;

	QVector<BookInfoBrief> infos;
	QStandardItemModel* mod;

private slots:
	void on_search_btn_clicked();
	void on_rtn_btn_clicked();
	void on_break_btn_clicked();
	void on_back_btn_clicked();
};

