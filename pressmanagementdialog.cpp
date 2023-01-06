#include "pressmanagementdialog.h"
#include "ui_pressmanagementdialog.h"

PressManagementDialog::PressManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PressManagementDialog)
{
    ui->setupUi(this);
}

PressManagementDialog::~PressManagementDialog()
{
    delete ui;
}

void PressManagementDialog::get_press_info()
{
	this->ui->id_edt->setText(QString::number(this->press_info.get_press_id()));
	this->ui->name_edt->setText(this->press_info.get_name());
	//this->ui->address_edt->setText(this->press_info.get_press_address());
}

void PressManagementDialog::on_search_btn_clicked()
{
	int press_id = this->ui->id_edt->text().toInt();
	QString press_name = this->ui->name_edt->text();
	//QString press_address = this->ui->address_edt->text();

	//this->press_info = DatabaseRepository::get_press_info(press_id, press_name);
	this->get_press_info();
}

void PressManagementDialog::on_add_btn_clicked()
{
	QString press_name = this->ui->name_edt->text();
	//QString press_address = this->ui->address_edt->text();

	//this->press_info = DatabaseRepository::add_press(press_name, press_address);
	this->get_press_info();
}

void PressManagementDialog::on_save_btn_clicked()
{
	int press_id = this->ui->id_edt->text().toInt();
	QString press_name = this->ui->name_edt->text();
	//QString press_address = this->ui->address_edt->text();

	//this->press_info = DatabaseRepository::update_press(press_id, press_name, press_address);
	this->get_press_info();
}

void PressManagementDialog::on_back_btn_clicked()
{
	this->close();
}

