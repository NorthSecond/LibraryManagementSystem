#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include <QMessagebox>

#include "bookinfo.h"
#include "databaseRepository.h"
#include "userinfo.h"

namespace Ui {
class userMainWindow;
}

class userMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userMainWindow(QWidget *parent = nullptr);
    ~userMainWindow();

private:
    Ui::userMainWindow *ui;
    QString nowStatus;
	unsigned long long userId;
	UserInfo user_info;
	QVector<BookInfo> infos;
	QStandardItemModel* mod;

public slots:
	void getLoginInfo(unsigned long long id);

private slots:
	void on_man_btn_clicked();
	void on_search_btn_clicked();
	void on_borrow_btn_clicked();
	void on_exit_btn_clicked();
};

