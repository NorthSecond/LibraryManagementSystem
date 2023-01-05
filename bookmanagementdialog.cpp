#include "bookmanagementdialog.h"
#include "ui_bookmanagementdialog.h"

BookManagementDialog::BookManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookManagementDialog)
{
    ui->setupUi(this);
}

BookManagementDialog::~BookManagementDialog()
{
    delete ui;
}
