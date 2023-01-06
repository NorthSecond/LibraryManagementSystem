#include "bookrtndialog.h"
#include "ui_bookrtndialog.h"

BookRtnDialog::BookRtnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookRtnDialog)
{
    ui->setupUi(this);

	mod = new QStandardItemModel();
	mod->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("书号")));
	mod->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("ISBN")));
	mod->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("书名")));
	mod->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("状态")));

	ui->search_res_tbl->setModel(mod);
	ui->search_res_tbl->setColumnWidth(0, 70);
	ui->search_res_tbl->setColumnWidth(1, 91);
	ui->search_res_tbl->setColumnWidth(2, 70);
	ui->search_res_tbl->setColumnWidth(3, 70);
	
	ui->search_res_tbl->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->search_res_tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(on_search_btn_clicked()));
	connect(ui->rtn_btn, SIGNAL(clicked()), this, SLOT(on_rtn_btn_clicked()));
	connect(ui->break_btn, SIGNAL(clicked()), this, SLOT(on_break_btn_clicked()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(on_back_btn_clicked()));	
}

BookRtnDialog::~BookRtnDialog()
{
    delete ui;
}

void BookRtnDialog::on_search_btn_clicked()
{
	infos.clear();
	mod->removeRows(0, mod->rowCount());
	DatabaseRepository repo;
	infos = db_repo->searchBookBrief(ui->lineEdit->text().toULongLong());
	for (int i = 0; i < infos.size(); i++)
	{
		mod->setItem(i, 0, new QStandardItem(QString::number(infos[i].get_book_index())));
		mod->setItem(i, 1, new QStandardItem(infos[i].get_ISBN()));
		mod->setItem(i, 2, new QStandardItem(infos[i].get_book_name()));
		mod->setItem(i, 3, new QStandardItem(infos[i].get_book_status() == LibraryBookInfo::onShelf ? "在架" :
			infos[i].get_book_status() == LibraryBookInfo::Borrowed ? "借出" : "损毁"));
	}
}

void BookRtnDialog::on_rtn_btn_clicked()
{
	if (ui->search_res_tbl->currentIndex().row() == -1)
	{
		QMessageBox::warning(this, "警告", "请先选择一本书");
		return;
	}
	if (infos[ui->search_res_tbl->currentIndex().row()].get_book_status() != LibraryBookInfo::Borrowed)
	{
		QMessageBox::warning(this, "警告", "该书未被借出");
		return;
	}
	if (db_repo->rtn_book(infos[ui->search_res_tbl->currentIndex().row()].get_book_index()))
	{
		QMessageBox::information(this, "提示", "还书成功");
	}
	else
	{
		QMessageBox::warning(this, "警告", "还书失败");
	}
}

void BookRtnDialog::on_break_btn_clicked()
{
	if (ui->search_res_tbl->currentIndex().row() == -1)
	{
		QMessageBox::warning(this, "警告", "请先选择一本书");
		return;
	}
	if (infos[ui->search_res_tbl->currentIndex().row()].get_book_status() != LibraryBookInfo::Borrowed)
	{
		QMessageBox::warning(this, "警告", "该书未被借出");
		return;
	}
	if (db_repo->break_book(infos[ui->search_res_tbl->currentIndex().row()].get_book_index()))
	{
		QMessageBox::information(this, "提示", "损坏登记成功");
	}
	else
	{
		QMessageBox::warning(this, "警告", "损坏登记失败");
	}
}

void BookRtnDialog::on_back_btn_clicked()
{
	this->close();
}