#include "readeraccountdialog.h"
#include "ui_readeraccountdialog.h"

ReaderAccountDialog::ReaderAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReaderAccountDialog)
{
    ui->setupUi(this);
}

ReaderAccountDialog::~ReaderAccountDialog()
{
    delete ui;
}
