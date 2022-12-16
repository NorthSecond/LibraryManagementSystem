#include "adminmainwidget.h"
#include "ui_adminmainwidget.h"

AdminMainWidget::AdminMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMainWidget)
{
    ui->setupUi(this);
}

AdminMainWidget::~AdminMainWidget()
{
    delete ui;
}
