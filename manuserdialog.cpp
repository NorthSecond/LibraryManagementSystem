#include "manuserdialog.h"
#include "ui_manuserdialog.h"

ManUserDialog::ManUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManUserDialog)
{
    ui->setupUi(this);
}

QString ManUserDialog::get_new_passwd()
{
	QString new_passwd = ui->passwd_edt->text();
	QString new_passwd_again = ui->passwd_2edt->text();

    if (new_passwd != new_passwd_again || new_passwd.isEmpty()) {
        return "";
    }
	return new_passwd;
}

ManUserDialog::~ManUserDialog()
{
    delete ui;
}

void ManUserDialog::getUserInfo(UserInfo info)
{
    this->ui->id_edt->setText(QString::number(info.get_user_id()));
	this->ui->uname_edt->setText(info.get_user_name());
    
    this->user_info = info;
}