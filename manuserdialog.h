#pragma once

#include <QDialog>
#include "databaseRepository.h"
#include "userinfo.h"

namespace Ui {
class ManUserDialog;
}

class ManUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManUserDialog(QWidget *parent = nullptr);
    QString get_new_passwd();
    ~ManUserDialog();

private:
    Ui::ManUserDialog *ui;
	UserInfo user_info;

public slots:
	void getUserInfo(UserInfo info);
};

