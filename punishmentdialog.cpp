#include "punishmentdialog.h"
#include "ui_punishmentdialog.h"

punishmentDialog::punishmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::punishmentDialog)
{
    ui->setupUi(this);

	mod = new QStandardItemModel();
	mod->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("序号")));
	mod->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("图书ID")));
	mod->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("图书名称")));
	mod->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("时间")));
	mod->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("类型")));
	mod->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("状态")));
	ui->res_tbl->setModel(mod);

	ui->res_tbl->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->res_tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));
	connect(ui->done_btn, SIGNAL(clicked()), this, SLOT(on_punishButton_clicked()));
	connect(ui->rtn_btn, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()));
}

punishmentDialog::~punishmentDialog()
{
    delete ui;
}


void punishmentDialog::on_searchButton_clicked()
{
	infos = db_repo->get_punish_info(ui->uname_edt->text().toULongLong());
	mod->removeRows(0, mod->rowCount());
	for (int i = 0; i < infos.size(); i++)
	{
		mod->setItem(i, 0, new QStandardItem(infos[i].get_id()));
		mod->setItem(i, 1, new QStandardItem(QString::number(infos[i].get_book_index())));
		//mod->setItem(i, 2, new QStandardItem(infos[i].book_name));
		mod->setItem(i, 3, new QStandardItem(infos[i].get_punish_time().toString("yyyy-MM-dd")));
		//mod->setItem(i, 4, new QStandardItem(infos[i].));
		if (infos[i].get_punish_type() == 0) {
			mod->setItem(i, 4, new QStandardItem("超时"));
		}
		else {
			mod->setItem(i, 4, new QStandardItem("损坏"));
		}
		if (infos[i].get_punish_status() == 0) {
			mod->setItem(i, 5, new QStandardItem("未处理"));
		}
		else {
			mod->setItem(i, 5, new QStandardItem("已处理"));
		}
	}
}

void punishmentDialog::on_punishButton_clicked()
{
	QModelIndex index = ui->res_tbl->selectionModel()->currentIndex();
	int row = index.row();
	if (row < 0 || row >= infos.size())
	{
		QMessageBox::warning(this, "警告", "请选择一条记录");
		return;
	}
	if (infos[row].get_punish_status() == 1)
	{
		QMessageBox::warning(this, "警告", "该记录已处理");
		return;
	}
	if (db_repo->punish(infos[row].get_id(), infos[row].get_user_id()))
	{
		QMessageBox::information(this, "提示", "处理成功");
		infos[row].set_punish_status(1);
		mod->setItem(row, 5, new QStandardItem("已处理"));
	}
	else
	{
		QMessageBox::warning(this, "警告", "处理失败");
	}
}

void punishmentDialog::on_backButton_clicked()
{
	this->close();
}