#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

	this->setWindowTitle("图书管理系统-管理员");
	//this->setWindowIcon(QIcon("icon.png"));
	
    this->ui->acc_man_wid = new AdminMainWidget("账户管理", this->ui->centralwidget);
	this->ui->book_man_wid = new AdminMainWidget("图书管理", this->ui->centralwidget);
	this->ui->rtn_man_wid = new AdminMainWidget("图书归还", this->ui->centralwidget);
	this->ui->ban_man_wid = new AdminMainWidget("违规管理", this->ui->centralwidget);
	
	this->ui->acc_man_wid->setGeometry(QRect(190, 10, 240, 160));
	this->ui->book_man_wid->setGeometry(QRect(450, 10, 240, 160));
	this->ui->rtn_man_wid->setGeometry(QRect(190, 180, 240, 160));
	this->ui->ban_man_wid->setGeometry(QRect(450, 180, 240, 160));

	connect(this->ui->acc_man_wid, SIGNAL(clicked(void)), this, SLOT(on_acc_man_clicked(void)));
	connect(this->ui->book_man_wid, SIGNAL(clicked(void)), this, SLOT(on_book_man_clicked(void)));
	connect(this->ui->rtn_man_wid, SIGNAL(clicked(void)), this, SLOT(on_book_rtn_clicked(void)));
	connect(this->ui->ban_man_wid, SIGNAL(clicked(void)), this, SLOT(on_ban_clicked(void)));
}


AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::getUserInfo(unsigned long long id)
{
	this->id = id;
	admin_info = db_repo->get_admin_info(id);
	this->ui->username_lbl->setText(admin_info.get_admin_name());
}

void AdminWindow::flush() {
	admin_info = db_repo->get_admin_info(id);
	this->ui->username_lbl->setText(admin_info.get_admin_name());
}

void AdminWindow::on_change_btn_clicked()
{
	QDialog* change_dialog = new changeAdminInfoDialog(this);
	connect(this, SIGNAL(sendAdminInfo(AdminInfo)), change_dialog, SLOT(getAdminInfo(AdminInfo)));
	connect(change_dialog, SIGNAL(close_signal()), this, SLOT(flush()));
	emit sendAdminInfo(admin_info);
	change_dialog->show();
}

void AdminWindow::on_exit_btn_clicked()
{
	exit(0);
}

void AdminWindow::on_acc_man_clicked()
{
	QDialog* dialog = new ReaderAccountDialog(this);
	connect(this, SIGNAL(sendAdminInfo(AdminInfo)), dialog, SLOT(getAdminInfo(AdminInfo)));
	emit sendAdminInfo(admin_info);
	dialog->show();
}

void AdminWindow::on_book_man_clicked()
{
	QDialog* dialog = new BookManagementDialog(this);
	connect(this, SIGNAL(sendAdminInfo(AdminInfo)), dialog, SLOT(getAdminInfo(AdminInfo)));
	emit sendAdminInfo(admin_info);
	dialog->show();
}

void AdminWindow::on_book_rtn_clicked()
{
	QDialog* dialog = new BookRtnDialog(this);
	connect(this, SIGNAL(sendAdminInfo(AdminInfo)), dialog, SLOT(getAdminInfo(AdminInfo)));
	emit sendAdminInfo(admin_info);
	dialog->show();
}

void AdminWindow::on_ban_clicked()
{
	QDialog* dialog = new punishmentDialog(this);
	connect(this, SIGNAL(sendAdminInfo(AdminInfo)), dialog, SLOT(getAdminInfo(AdminInfo)));
	emit sendAdminInfo(admin_info);
	dialog->show();
}

// exit when close
void AdminWindow::closeEvent(QCloseEvent* event)
{
	exit(0);
}