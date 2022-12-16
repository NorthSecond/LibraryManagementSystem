#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), db()
{
    ui->setupUi(this);

    this->setFixedSize(window_width, window_height);
    this->setWindowTitle("图书管理系统-请登录");
    //this->setWindowIcon(QIcon("icon.png"));

    username_lbl = new QLabel(this);
    username_lbl->setText("账户名：");
    username_lbl->setGeometry(120, 50, 50, 30);
    username_lbl->setStyleSheet("font-size:12px;font - weight:bold; font - family:Arial");

    passwd_lbl = new QLabel(this);
    passwd_lbl->setText("密码：");
    passwd_lbl->setGeometry(120, 90, 50, 30);
    passwd_lbl->setStyleSheet("font-size:12px;font - weight:bold; font - family:Arial");

    identity_lbl = new QLabel(this);
    identity_lbl->setText("身份：");
    identity_lbl->setGeometry(120, 130, 50, 30);
    identity_lbl->setStyleSheet("font-size:12px;font - weight:bold; font - family:Arial");

    username_edit = new QLineEdit(this);
    username_edit->setGeometry(180, 50, 80, 30);
    passwd_edit = new QLineEdit(this);
    passwd_edit->setGeometry(180, 90, 80, 30);

    identity_box = new QComboBox(this);
    identity_box->addItem(QString::asprintf("用户"));
    identity_box->addItem(QString::asprintf("管理员"));
    identity_box->setGeometry(180, 130, 50, 30);

    login_btn = new QPushButton(this);
    login_btn->setText(QString::asprintf("登陆"));
    login_btn->setGeometry(300, 250, 50, 30);

    exit_btn = new QPushButton(this);
    exit_btn->setText(QString::asprintf("退出"));
    exit_btn->setGeometry(420, 250, 50, 30);


    connect(login_btn, &QPushButton::clicked, this, &MainWindow::login_btn_pushed);
    connect(exit_btn, &QPushButton::clicked, this, &MainWindow::exit_btn_pushed);
}

MainWindow::~MainWindow()
{
    if(username_lbl != nullptr){
        delete username_lbl;
    }
    if(passwd_lbl != nullptr) {
        delete passwd_lbl;
    }
    if(identity_lbl != nullptr) {
        delete identity_lbl;
    }
    if(username_edit != nullptr) {
        delete username_edit;
    }
    if(passwd_edit != nullptr) {
        delete passwd_edit;
    }
    if(identity_box!= nullptr) {
        delete identity_box;
    }
    if(login_btn != nullptr){
        delete login_btn;
    }
    if(exit_btn!= nullptr){
        delete exit_btn;
    }
    // TODO: FInish delete sentences.
    delete ui;
}

void MainWindow::login_btn_pushed(){
//    QMessageBox::critical(NULL, "Info", "TODO");
    QString user_name = username_edit->text();
    QString passwd = passwd_edit->text();
    Role role;
    size_t identity_index = identity_box->currentIndex();
    switch(identity_index){
    case 0:
        role = Role::STUDENT;
        break;
    case 1:
        role = Role::TEACHER;
        break;
    case 2:
        role = Role::Admin;
        break;
    case 3:
        role = Role::OUTCOME;
        break;
    default:
        throw("Undefined role\n");
        exit(3);
        break;
    }
    long long uid = db.login(user_name, passwd, role);
    if(uid < 0){
        QMessageBox::warning(NULL, "登陆失败！", "用户名或密码错误");
    }else {
        // TODO: Add different userType
        // 使用槽函数进行窗口的数据传播
        std::unique_ptr<QWidget> newWidget;
        newWidget.reset(new AdminMainWidget());
//        QWidget* newWidget = new AdminMainWidget();
//        if(uid == 0){
//            newWidget = new AdminMainWidget();
//        }else if(uid == 1){
//            newWidget = new AdminMainWidget();
//        }else if(uid == 2){
//            newWidget = new AdminMainWidget();
//        }else if(uid == 3){
//            newWidget = new AdminMainWidget();
//        }
        newWidget->show();
        this->hide();
    }
}

void MainWindow::exit_btn_pushed() {
    exit(0);
}
