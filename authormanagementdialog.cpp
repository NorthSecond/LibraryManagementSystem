#include "authormanagementdialog.h"
#include "ui_authormanagementdialog.h"

AuthorManageMentDialog::AuthorManageMentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorManageMentDialog)
{
    ui->setupUi(this);
}

AuthorManageMentDialog::~AuthorManageMentDialog()
{
    delete ui;
}
