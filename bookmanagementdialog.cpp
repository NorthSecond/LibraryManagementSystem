#include "bookmanagementdialog.h"
#include "ui_bookmanagementdialog.h"

BookManagementDialog::BookManagementDialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::BookManagementDialog)
{
	ui->setupUi(this);

	// 设置 ISBN_ra 和 idx_ra 为互斥
	ui->ISBN_ra->setAutoExclusive(true);
	ui->idx_ra->setAutoExclusive(true);

	mod = new QStandardItemModel(this);
	mod->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("书号")));
	mod->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("ISBN")));
	mod->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("书名")));
	mod->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("状态")));

	ui->tableView->setModel(mod);
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	// 设置按钮组和互斥
	btnGroup = new QButtonGroup(this);
	btnGroup->addButton(ui->ISBN_ra);
	btnGroup->addButton(ui->idx_ra);
	btnGroup->setExclusive(true);
	// 设置默认选中 ISBN_ra
	ui->ISBN_ra->setChecked(true);

	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(on_search_btn_clicked()));
	connect(ui->new_bookinfo_btn, SIGNAL(clicked()), this, SLOT(on_add_book_info_btn_clicked()));
	connect(ui->save_bookinfo_btn, SIGNAL(clicked()), this, SLOT(on_modify_book_info_btn_clicked()));
	connect(ui->new_book_btn, SIGNAL(clicked()), this, SLOT(on_add_book_btn_clicked()));
	connect(ui->save_book_btn, SIGNAL(clicked()), this, SLOT(on_modify_book_btn_clicked()));
	connect(ui->delete_book_btn, SIGNAL(clicked()), this, SLOT(on_delete_book_btn_clicked()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(on_back_btn_clicked()));
}

BookManagementDialog::~BookManagementDialog()
{
	delete ui;
}

void BookManagementDialog::getAdminInfo(AdminInfo info)
{
	admin_info = info;
}

void BookManagementDialog::on_mod_selected() {

}

void BookManagementDialog::on_search_btn_clicked()
{
	// 清空表格
	mod->removeRows(0, mod->rowCount());

	// 获取输入的关键字
	QString keyword = ui->isbn_edt->text();

	// 获取选中的按钮
	QAbstractButton* btn = btnGroup->checkedButton();
	if (btn == ui->ISBN_ra) {
		// 按 ISBN 查询
		now_book = db_repo->get_book_by_ISBN(keyword);
		infos.clear();
		infos = db_repo->get_books_by_ISBN(keyword);
	}
	else if (btn == ui->idx_ra) {
		// 按书号查询
		now_book = db_repo->get_book_by_index(keyword.toULongLong()).get_book();
		infos.clear();
		infos.push_back(db_repo->get_book_by_index(keyword.toULongLong()));
	}
	else {
		// 未选中任何按钮
		QMessageBox::warning(this, "错误", "请选择查询方式");
		return;
	}

	if (now_book.get_ISBN() == "") {
		QMessageBox::warning(this, "错误", "未找到该书");
		return;
	}

	// 显示查询结果
	for (int i = 0; i < infos.size(); i++) {
		mod->setItem(i, 0, new QStandardItem(QString::number(infos[i].get_book_index())));
		mod->setItem(i, 1, new QStandardItem(infos[i].get_book().get_ISBN()));
		mod->setItem(i, 2, new QStandardItem(infos[i].get_book().get_book_name()));
		mod->setItem(i, 3, new QStandardItem(infos[i].get_book_status() == LibraryBookInfo::onShelf ?
			"在架上" : infos[i].get_book_status() == LibraryBookInfo::Borrowed ? "借出" : "损毁"));
	}

	// 图书内容显示
	ui->book_name_edt->setText(now_book.get_book_name());
	ui->lang_edt->setText(now_book.get_language_info());
	ui->press_edt->setText(now_book.get_press_name());
	ui->auth_edt->setText(now_book.get_author_name());
	ui->ver_edt->setText(now_book.get_book_version());
	ui->brief_edt->setText(now_book.get_book_brief());
}

void BookManagementDialog::on_add_book_btn_clicked()
{
	if (db_repo->addBook(now_book, LibraryBookInfo::onShelf)) {
		QMessageBox::information(this, "提示", "添加成功");
	}
	else {
		QMessageBox::warning(this, "错误", "添加失败");
	}

	on_search_btn_clicked();
}

void BookManagementDialog::on_modify_book_btn_clicked()
{
	// 获取选中的行
	QModelIndex index = ui->tableView->selectionModel()->currentIndex();
	if (!index.isValid()) {
		QMessageBox::warning(this, "错误", "未选中任何行");
		return;
	}
	int row = index.row();
	
	// 获取选中的书号
	QString book_index = mod->item(row, 0)->text();
	// 获取选中的状态
	QString status = mod->item(row, 3)->text();
	// 获取选中的状态对应的枚举值
	LibraryBookInfo::bookStatus book_status = LibraryBookInfo::onShelf;
	if (status == "在架上") {
		book_status = LibraryBookInfo::onShelf;
	}
	else if (status == "借出") {
		book_status = LibraryBookInfo::Borrowed;
	}
	else if (status == "损毁") {
		book_status = LibraryBookInfo::Wartung;
	}
	else {
		QMessageBox::warning(this, "错误", "未知的状态");
		return;
	}

	// 修改数据库
	if (db_repo->modifyBook(book_index.toULongLong(), book_status)) {
		QMessageBox::information(this, "提示", "修改成功");
	}
	else {
		QMessageBox::warning(this, "错误", "修改失败");
	}

	on_search_btn_clicked();
}

void BookManagementDialog::on_delete_book_btn_clicked()
{
	// 获取选中的行
	QModelIndex index = ui->tableView->selectionModel()->currentIndex();
	if (!index.isValid()) {
		QMessageBox::warning(this, "错误", "未选中任何行");
		return;
	}
	int row = index.row();
	// 获取选中的书号
	QString book_index = mod->item(row, 0)->text();

	// 二次确认
	if (QMessageBox::question(this, "提示", "确认删除该书？") == QMessageBox::Yes) {
		// 删除数据库中的记录
		if (db_repo->deleteBook(book_index.toLongLong())) {
			QMessageBox::information(this, "提示", "删除成功");
		}
		else {
			QMessageBox::warning(this, "错误", "删除失败");
		}
	}
	on_search_btn_clicked();
}

void BookManagementDialog::on_add_book_info_btn_clicked()
{
	// 获取输入内容	
	QString ISBN = ui->isbn_edt->text();
	QString book_name = ui->book_name_edt->text();
	QString lang = ui->lang_edt->text();
	QString press = ui->press_edt->text();
	QString auth = ui->auth_edt->text();
	QString ver = ui->ver_edt->text();
	QString brief = ui->brief_edt->toPlainText();

	// 检查输入内容
	if (ISBN == "" || book_name == "" || press == "" || auth == "") {
		QMessageBox::warning(this, "错误", "输入内容不能为空");
		return;
	}

	// 设置图书信息

	LibraryBookInfo::AuthorInfo author(0, auth);
	LibraryBookInfo::PressInfo press_info(0, press);

	unsigned long long author_id = db_repo->add_author_info(author);
	unsigned long long press_id = db_repo->add_press_info(press_info);

	author.set_author_id(author_id);
	press_info.set_press_id(press_id);

	LibraryBookInfo::Book newBook(ISBN, book_name, press_info, author, lang, ver, brief);
	if (db_repo->addBookInfo(newBook)) {
		QMessageBox::information(this, "提示", "添加成功");
	}
	else {
		QMessageBox::warning(this, "错误", "添加失败");
	}

}

void BookManagementDialog::on_modify_book_info_btn_clicked()
{
	// 获取输入内容	
	QString book_name = ui->book_name_edt->text();
	QString lang = ui->lang_edt->text();
	QString press = ui->press_edt->text();
	QString auth = ui->auth_edt->text();
	QString ver = ui->ver_edt->text();
	QString brief = ui->brief_edt->toPlainText();

	// 检查输入内容
	if (book_name == "" || press == "" || auth == "") {
		QMessageBox::warning(this, "错误", "输入内容不能为空");
		return;
	}

	// 设置图书信息
	LibraryBookInfo::AuthorInfo author(0, auth);
	LibraryBookInfo::PressInfo press_info(0, press);

	unsigned long long author_id = db_repo->add_author_info(author);
	unsigned long long press_id = db_repo->add_press_info(press_info);

	author.set_author_id(author_id);
	press_info.set_press_id(press_id);

	LibraryBookInfo::Book newBook(now_book.get_ISBN(), book_name, press_info, author, lang, ver, brief);

	// 修改数据库
	if (db_repo->update_book_info(now_book.get_ISBN(), newBook)) {
		QMessageBox::information(this, "提示", "修改成功");
	}
	else {
		QMessageBox::warning(this, "错误", "修改失败");
	}

	on_search_btn_clicked();
}

void BookManagementDialog::on_back_btn_clicked()
{
	this->close();
}
