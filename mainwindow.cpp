#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QFont font("Microsoft YaHei", 12, 75);

	this->setWindowTitle("图书管理系统-请登录");
	//this->setWindowIcon(QIcon("icon.png"));
	this->setFixedSize(320, 240);

	user_label = new QLabel(this);
	user_label->setText("用户名:");
	user_label->setGeometry(30, 40, 80, 25);
	user_label->setFont(font);
	user_label->setAlignment(Qt::AlignRight);

	password_label = new QLabel(this);
	password_label->setText("密  码:");
	password_label->setGeometry(30, 90, 80, 25);
	password_label->setFont(font);
	password_label->setAlignment(Qt::AlignRight);

	role_label = new QLabel(this);
	role_label->setText("身  份:");
	role_label->setGeometry(30, 140, 80, 25);
	role_label->setFont(font);
	role_label->setAlignment(Qt::AlignRight);

	user_line = new QLineEdit(this);
	user_line->setFont(font);
	user_line->setGeometry(120, 40, 140, 25);

	password_line = new QLineEdit(this);
	password_line->setGeometry(120, 90, 140, 25);
	password_line->setFont(font);
	password_line->setEchoMode(QLineEdit::Password);

	role_combo = new QComboBox(this);
	role_combo->setGeometry(120, 140, 140, 25);
	role_combo->setFont(font);
	role_combo->addItem("管理员");
	role_combo->addItem("学生");
	role_combo->addItem("教师");
	role_combo->addItem("外来人员");


	login_btn = new QPushButton(this);
	login_btn->setText("登录");
	login_btn->setFont(font);
	login_btn->setGeometry(40, 190, 75, 25);

	exit_btn = new QPushButton(this);
	exit_btn->setText("退出");
	exit_btn->setFont(font);
	exit_btn->setGeometry(190, 190, 75, 25);

	connect(login_btn, &QPushButton::clicked, this, &MainWindow::login_btn_pushed);
	connect(exit_btn, &QPushButton::clicked, this, &MainWindow::exit_btn_pushed);
}

MainWindow::~MainWindow()
{
	if (user_label != nullptr) {
		delete user_label;
	}
	if (password_label != nullptr) {
		delete password_label;
	}
	if (role_label != nullptr) {
		delete role_label;
	}
	if (user_line != nullptr) {
		delete user_line;
	}
	if (password_line != nullptr) {
		delete password_line;
	}
	if (role_combo != nullptr) {
		delete role_combo;
	}
	if (login_btn != nullptr) {
		delete login_btn;
	}
	if (exit_btn != nullptr) {
		delete exit_btn;
	}
	delete ui;
}

void MainWindow::login_btn_pushed()
{
	QString user = user_line->text();
	QString password = password_line->text();
	QString role = role_combo->currentText();
	if (user.isEmpty() || password.isEmpty()) {
		QMessageBox::warning(this, "警告", "用户名或密码不能为空");
		return;
		if (password.isEmpty()) {
			password_line->setFocus();
		}
		if (user.isEmpty()) {
			user_line->setFocus();
		}
	}
	else {
		User::Role role_id = User::Role::ADMIN;
		if (role == QString::fromStdString("管理员")
			|| role == QString::fromStdString("admin")) {
			role_id = User::Role::ADMIN;
		}
		else if (role == QString::fromStdString("学生")
			|| role == QString::fromStdString("student")) {
			role_id = User::Role::STUDENT;
		}
		else if (role == QString::fromStdString("教师")
			|| role == QString::fromStdString("teacher")) {
			role_id = User::Role::TEACHER;
		}
		else if (role == QString::fromStdString("外来人员")
			|| role == QString::fromStdString("visitor")) {
			role_id = User::Role::OUTCOME;
		}
		
		unsigned long long login_res = db_repo->login(user, password, role_id);

		if (login_res) {
			// success
			if (role_id == User::ADMIN) {
				// admin main window
				QWidget* adminWid = new AdminWindow(this);
				emit sendLoginInfo(login_res);
				adminWid->show();
				this->hide();
			}
			else {
				emit sendLoginInfo(login_res);
			}
		}
		else {
			// login failed
			QMessageBox::warning(this, "错误", "用户名或密码错误", "确定");
		}
	}
}

void MainWindow::exit_btn_pushed()
{
	exit(0);
}

//void MainWindow::closeEvent(QCloseEvent* event)
//{
//	exit(0);
//}