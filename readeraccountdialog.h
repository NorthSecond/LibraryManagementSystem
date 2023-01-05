#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QMessagebox>

#include "userinfo.h"
#include "databaseRepository.h"

namespace Ui {
class ReaderAccountDialog;
}

class ReaderAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReaderAccountDialog(QWidget *parent = nullptr);
    ~ReaderAccountDialog();

private:
    Ui::ReaderAccountDialog *ui;
	AdminInfo admin_info;
    QVector<UserInfo> user_list;
    QStandardItemModel* mod;

    void flush_table();

public slots:
	void getAdminInfo(AdminInfo info);
    
private slots:
	void on_mod_selected();
    
	void on_add_btn_clicked();
	void on_change_btn_clicked();
	void on_del_btn_clicked();
	void on_back_btn_clicked();
};

