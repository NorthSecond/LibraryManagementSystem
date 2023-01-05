#include "changeadmininfodialog.h"
#include "ui_changeadmininfodialog.h"

changeAdminInfoDialog::changeAdminInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeAdminInfoDialog)
{
    ui->setupUi(this);
}

changeAdminInfoDialog::~changeAdminInfoDialog()
{
    delete ui;
}
