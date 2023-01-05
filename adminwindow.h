#pragma once

#include <QMainWindow>
#include <QMessagebox>

#include "databaseRepository.h"
#include "adminmainwidget.h"
#include "userinfo.h"
#include "changeadmininfodialog.h"
#include "readeraccountdialog.h"
#include "bookmanagementdialog.h"
#include "bookrtndialog.h"
#include "punishmentdialog.h"


namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

protected:
    void closeEvent(QCloseEvent* event);
    
private:
    Ui::AdminWindow *ui;
	unsigned long long id;
	AdminInfo admin_info;
    
signals:
    void sendAdminInfo(AdminInfo);

public slots:
    void getUserInfo(unsigned long long id);
	void flush();

private slots:
    void on_change_btn_clicked();
    void on_exit_btn_clicked();

    void on_acc_man_clicked();
    void on_book_man_clicked();
    void on_book_rtn_clicked();
    void on_ban_clicked();
};

