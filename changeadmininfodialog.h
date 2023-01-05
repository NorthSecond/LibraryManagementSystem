#pragma once

#include <QDialog>

#include "userinfo.h"
#include "databaseRepository.h"

namespace Ui {
class changeAdminInfoDialog;
}

class changeAdminInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeAdminInfoDialog(QWidget *parent = nullptr);
    ~changeAdminInfoDialog();

private:
    Ui::changeAdminInfoDialog *ui;
    AdminInfo admin_info;

public slots:
	void getAdminInfo(AdminInfo info);

private slots:
    void commit_change();
    void back_btn_clicked();
};

