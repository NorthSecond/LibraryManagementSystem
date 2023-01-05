#include "punishmentdialog.h"
#include "ui_punishmentdialog.h"

punishmentDialog::punishmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::punishmentDialog)
{
    ui->setupUi(this);
}

punishmentDialog::~punishmentDialog()
{
    delete ui;
}
