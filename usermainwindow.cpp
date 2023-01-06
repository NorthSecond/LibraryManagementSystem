#include "usermainwindow.h"
#include "ui_usermainwindow.h"

userMainWindow::userMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userMainWindow)
{
    ui->setupUi(this);

    nowStatus = "正常";
	ui->stat_lbl->setText(nowStatus);
    
    // model
	mod = new QStandardItemModel(this);
    mod->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("书号")));
    mod->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("ISBN")));
    mod->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("书名")));
    mod->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("状态")));
	mod->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("作者")));
	mod->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出版社")));
	mod->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("介绍")));
	mod->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("版本号")));

	ui->tableView->setModel(mod);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    

	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(on_search_btn_clicked()));
	connect(ui->borrow_btn, SIGNAL(clicked()), this, SLOT(on_borrow_btn_clicked()));
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_exit_btn_clicked()));
	connect(ui->man_btn, SIGNAL(clicked()), this, SLOT(on_man_btn_clicked()));
}

userMainWindow::~userMainWindow()
{
    delete ui;
}

void userMainWindow::getLoginInfo(unsigned long long id)
{
	userId = id;
	user_info = db_repo->get_user(id);
	nowStatus = user_info.get_user_status() == User::Normal ? "正常" : "被禁用";
	ui->stat_lbl->setText(nowStatus);
}

void userMainWindow::on_man_btn_clicked() {
	ManUserDialog* manUserDialog = new ManUserDialog(this);
	connect(this, SIGNAL(sendUserInfo(UserInfo)), manUserDialog, SLOT(getLoginInfo(UserInfo)));
	emit sendUserInfo(user_info);

	auto reply = manUserDialog->exec();
	if (reply == QDialog::Accepted) {
		// 更改密码
		unsigned long long id = user_info.get_user_id();
		QString new_pwd = manUserDialog->get_new_passwd();
		if (new_pwd == "") {
			QMessageBox::warning(this, "警告", "请输入两次不为空的相同密码");
			return;
		}
		db_repo->change_user_pwd(id, new_pwd);
	}
}

void userMainWindow::on_search_btn_clicked()
{
	QString ISBN = ui->ISBN_edt->text();
	QString name = ui->name_edt->text();
    
	if (ISBN.isEmpty() && name.isEmpty())
	{
		QMessageBox::warning(this, "警告", "请输入ISBN或书名");
		return;
	}
	else if (!ISBN.isEmpty())
	{
		infos = (QVector<BookInfo>)db_repo->get_books_by_ISBN(ISBN);
	}
	else {
		infos = (QVector<BookInfo>)db_repo->get_books_by_name(name);
	}
	
	mod->clear();
	if (infos.size() == 0)
	{
		QMessageBox::warning(this, "警告", "没有找到相关书籍");
		return;
	}
	else {
		
		for (size_t i = 0; i < infos.size(); ++i) {
			mod->setItem(i, 0, new QStandardItem(QString::number(infos[i].get_book_index())));
			mod->setItem(i, 1, new QStandardItem(infos[i].get_book().get_ISBN()));
			mod->setItem(i, 2, new QStandardItem(infos[i].get_book().get_book_name()));
			mod->setItem(i, 3, new QStandardItem(infos[i].get_book_status() == LibraryBookInfo::onShelf ? "在架上" :
				infos[i].get_book_status() == LibraryBookInfo::Borrowed ? "被借出" : "损毁"));
			mod->setItem(i, 4, new QStandardItem(infos[i].get_book().get_author_name()));
			mod->setItem(i, 5, new QStandardItem(infos[i].get_book().get_press_name()));
			mod->setItem(i, 6, new QStandardItem(infos[i].get_book().get_book_brief()));
			mod->setItem(i, 7, new QStandardItem(infos[i].get_book().get_book_version()));
		}
	}
}

void userMainWindow::on_borrow_btn_clicked()
{
	if (nowStatus == "被禁用")
	{
		QMessageBox::warning(this, "警告", "您已被禁用，无法借书");
		return;
	}
	if (ui->tableView->currentIndex().row() == -1)
	{
		QMessageBox::warning(this, "警告", "请选择一本书");
		return;
	}
	int row = ui->tableView->currentIndex().row();
	BookInfo info = infos[row];
	if (info.get_book_status() != LibraryBookInfo::onShelf)
	{
		QMessageBox::warning(this, "警告", "该书已被借出或损毁");
		return;
	}
	
	// 检查限额
	if (db_repo->is_user_limited(userId))
	{
		QMessageBox::warning(this, "警告", "您已达到借书上限");
		return;
	}
	if (db_repo->borrow_book(userId, info.get_book_index()))
	{
		QMessageBox::information(this, "提示", "借书成功");
	}
	else
	{
		QMessageBox::warning(this, "警告", "借书失败");
	}
}

void userMainWindow::on_exit_btn_clicked()
{
	exit(0);
}
