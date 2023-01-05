#include "changeadmininfodialog.h"
#include "ui_changeadmininfodialog.h"

changeAdminInfoDialog::changeAdminInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeAdminInfoDialog)
{
    ui->setupUi(this);
    
}

changeAdminInfoDialog::~changeAdminInfoDialog()
{
    delete ui;
}

void changeAdminInfoDialog::getAdminInfo(AdminInfo info)
{
	this->admin_info = info;
	this->ui->id_edt->setText(QString::number(this->admin_info.get_admin_id()));
	this->ui->user_name_edt->setText(this->admin_info.get_admin_name());
	this->ui->phone_edt->setText(this->admin_info.get_connection_info().get_telephone());
}

void changeAdminInfoDialog::commit_change() 
{
	if (this->ui->passwd_edt->text().length() || this->ui->new_passwd_wdt->text().length())
	{
		if (this->ui->passwd_edt->text() != this->ui->new_passwd_wdt->text())
		{
			QMessageBox::warning(this, "警告", "两次输入的密码不一致");
			return;
		}
		else
		{
			if (!db_repo->change_admin_passwd(this->admin_info.get_admin_id(), this->ui->passwd_edt->text())) {
				QMessageBox::warning(this, "警告", "密码修改失败");
				return;
			}
			//this->admin_info.set_password(this->ui->passwd_edt->text().toStdString());
		}
	}
	// other change
	this->admin_info.set_admin_name(this->ui->user_name_edt->text());
	this->admin_info.set_connection_info(ConnectionInfo(this->admin_info.get_connection_info().get_connection_id(), 
		this->ui->phone_edt->text()));

	if (db_repo->update_admin_info(this->admin_info))
	{
		QMessageBox::information(this, "提示", "修改成功");
		this->close();
	}
	else
	{
		QMessageBox::warning(this, "警告", "修改失败");
	}
}

void changeAdminInfoDialog::back_btn_clicked()
{
	this->close();
}