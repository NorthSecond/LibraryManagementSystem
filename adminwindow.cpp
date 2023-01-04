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

	//connect(parent, SIGNAL(sendLoginInfo(QString)), this, SLOT(getUserInfo(QString)));
}

// 设置鼠标点击事件
bool AdminWindow::eventFilter(QObject* obj, QEvent* e)
{
	if (e->type() == QEvent::MouseButtonPress)
	{
		if (obj == this->ui->acc_man_wid) {
			// TODO: 
			QMessageBox::information(this, "调用", "账户管理");
		}
		else if (obj == this->ui->book_man_wid) {
			QMessageBox::information(this, "调用", "图书管理");
		}
		else if(obj == this->ui->rtn_man_wid) {
			QMessageBox::information(this, "调用", "图书归还");
		}
		else if (obj == this->ui->ban_man_wid) {
			QMessageBox::information(this, "调用", "违规管理");
		}
	}
	return false;
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

void AdminWindow::on_change_btn_clicked()
{
}

void AdminWindow::on_exit_btn_clicked()
{
	exit(0);
}