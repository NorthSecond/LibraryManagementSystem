#include "readeraccountdialog.h"
#include "ui_readeraccountdialog.h"

ReaderAccountDialog::ReaderAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReaderAccountDialog)
{
    ui->setupUi(this);

	mod = new QStandardItemModel(this);
	mod->setHorizontalHeaderItem(0, new QStandardItem("ID"));
	mod->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
	mod->setHorizontalHeaderItem(2, new QStandardItem("手机号"));
	mod->setHorizontalHeaderItem(3, new QStandardItem("读者类型"));
	mod->setHorizontalHeaderItem(4, new QStandardItem("借书数量"));
	mod->setHorizontalHeaderItem(5, new QStandardItem("读者状态"));
    
	this->ui->acc_tbl->setModel(mod);
	flush_table();

	ui->acc_tbl->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->acc_tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// connect( view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(handleSelectionChanged(const QItemSelection &, const QItemSelection &)) );
	
	// select
	connect(ui->acc_tbl->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(on_mod_selected()));
	connect(ui->new_btn, SIGNAL(clicked()), this, SLOT(on_add_btn_clicked()));
	connect(ui->change_btn, SIGNAL(clicked()), this, SLOT(on_change_btn_clicked()));
	connect(ui->del_btn, SIGNAL(clicked()), this, SLOT(on_del_btn_clicked()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(on_back_btn_clicked()));
}

void ReaderAccountDialog::flush_table() {
	user_list = db_repo->get_user_list();
	for (size_t i = 0; i < user_list.size(); i++)
	{
		mod->setItem(i, 0, new QStandardItem(QString::number(user_list[i].get_user_id())));
		mod->setItem(i, 1, new QStandardItem(user_list[i].get_user_name()));
		mod->setItem(i, 2, new QStandardItem(user_list[i].get_connection_info().get_telephone()));
		//mod->setItem(i, 3, new QStandardItem(user_list[i].get_user_type()));
		switch (user_list[i].get_user_role())
		{
		case User::TEACHER:
			mod->setItem(i, 3, new QStandardItem("教师"));
			break;
		case User::STUDENT:
			mod->setItem(i, 3, new QStandardItem("学生"));
			break;
		case User::OUTCOME:
			mod->setItem(i, 3, new QStandardItem("外来人员"));
			break;
		}
		mod->setItem(i, 4, new QStandardItem(QString::number(user_list[i].get_borrowed_num())));
		//mod->setItem(i, 5, new QStandardItem(QString::fromStdString(user_list[i].get_user_status())));
		switch (user_list[i].get_user_status())
		{
		case User::Normal:
			mod->setItem(i, 5, new QStandardItem("正常"));
			break;
		default:
			mod->setItem(i, 5, new QStandardItem("受限"));
			break;
		}
	}
}

ReaderAccountDialog::~ReaderAccountDialog()
{
	if (mod != nullptr){
		delete mod;
	}
    delete ui;
}

void ReaderAccountDialog::getAdminInfo(AdminInfo info)
{
	this->admin_info = info;
}


void ReaderAccountDialog::on_mod_selected()
{
	QModelIndex index = ui->acc_tbl->selectionModel()->currentIndex();
	int row = index.row();
	if (row < 0 || row >= user_list.size()) {
		return;
	}
	ui->id_edt->setText(QString::number(user_list[row].get_user_id()));
	ui->name_edt->setText(user_list[row].get_user_name());
	ui->phone_edt->setText(user_list[row].get_connection_info().get_telephone());
	ui->type_cbox->setCurrentIndex(user_list[row].get_user_role());
	if (user_list[row].get_user_status() == User::Normal)
		ui->stat_edt->setCurrentIndex(0);
	else
		ui->stat_edt->setCurrentIndex(1);
	ui->borrow_num_edt->setText(QString::number(user_list[row].get_borrowed_num()));
	
}

void ReaderAccountDialog::on_add_btn_clicked()
{
	if (ui->name_edt->text().isEmpty() || ui->phone_edt->text().isEmpty() || ui->type_cbox->currentIndex() == -1 || ui->stat_edt->currentIndex() == -1)
	{
		QMessageBox::warning(this, "警告", "请填写完整信息");
		return;
	}
	
	User::Role role = User::Role(ui->type_cbox->currentIndex());
	User::Status status = User::Status(ui->stat_edt->currentIndex());
	
	ConnectionInfo info(0, ui->phone_edt->text());
	
	UserInfo user = UserInfo(0, ui->name_edt->text(), role, status, info);

	if(db_repo->add_user(user)){
		QMessageBox::information(this, "提示", "添加成功");
		flush_table();
	}
	else {
		QMessageBox::warning(this, "警告", "添加失败");
	}
	flush_table();	
}

void ReaderAccountDialog::on_change_btn_clicked()
{
	if (ui->name_edt->text() == "0" || ui->phone_edt->text().isEmpty() || ui->type_cbox->currentIndex() == -1 || ui->stat_edt->currentIndex() == -1)
	{
		QMessageBox::warning(this, "警告", "请填写完整信息");
		return;
	}
	User::Role role = User::Role(ui->type_cbox->currentIndex());
	User::Status status = User::Status(ui->stat_edt->currentIndex());

	//ConnectionInfo info(db_repo->get_user(ui->id_edt->text().toULongLong()).get_connection_info()., ui->phone_edt->text());
	ConnectionInfo info = db_repo->get_user(ui->id_edt->text().toULongLong()).get_connection_info();
	info.set_telephone(ui->phone_edt->text());
	UserInfo user = UserInfo(ui->id_edt->text().toInt(), ui->name_edt->text(), role, status, info);

	if(db_repo->update_user(user)){
		QMessageBox::information(this, "提示", "修改成功");
		flush_table();
	}
	else {
		QMessageBox::warning(this, "警告", "修改失败");
	}
	flush_table();
}

void ReaderAccountDialog::on_del_btn_clicked()
{
	// 二次确认
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "确认", "确认删除？", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		db_repo->delete_user(ui->id_edt->text().toULongLong());
	}
	else {
		return;
	}
	flush_table();
}

void ReaderAccountDialog::on_back_btn_clicked()
{
	this->close();
}