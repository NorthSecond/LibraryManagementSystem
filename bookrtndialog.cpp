#include "bookrtndialog.h"
#include "ui_bookrtndialog.h"

BookRtnDialog::BookRtnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookRtnDialog)
{
    ui->setupUi(this);
}

BookRtnDialog::~BookRtnDialog()
{
    delete ui;
}
