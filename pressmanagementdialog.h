#pragma once

#include <QDialog>

#include "databaseRepository.h"
#include "bookinfo.h"

namespace Ui {
class PressManagementDialog;
}

class PressManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PressManagementDialog(QWidget *parent = nullptr);
    ~PressManagementDialog();

private:
    Ui::PressManagementDialog *ui;
	LibraryBookInfo::PressInfo press_info;

public slots:
    void get_press_info();

	void on_search_btn_clicked();
	void on_add_btn_clicked();
	void on_save_btn_clicked();
	void on_back_btn_clicked();
};

