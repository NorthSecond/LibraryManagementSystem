#include "adminmainwidget.h"
#include "ui_adminmainwidget.h"

AdminMainWidget::AdminMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMainWidget)
{
    ui->setupUi(this);
}

AdminMainWidget::AdminMainWidget(QGraphicsView* view, QString name, QWidget* parent) :
	QWidget(parent),
	ui(new Ui::AdminMainWidget)
{
	ui->setupUi(this);
	ui->grap->setScene(view->scene());
	ui->name_lbl->setText(name);
}

AdminMainWidget::AdminMainWidget(QString name, QWidget* parent) :
	QWidget(parent),
	ui(new Ui::AdminMainWidget)
{
	ui->setupUi(this);
	ui->name_lbl->setText(name);
}

void AdminMainWidget::setGrap(QGraphicsView* view)
{
	this->ui->grap = view;
}

void AdminMainWidget::setNameLbl(QString name)
{
	this->ui->name_lbl->setText(name);
}

void AdminMainWidget::mouseReleaseEvent(QMouseEvent* ev)
{
	Q_UNUSED(ev)
	if (ev->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

AdminMainWidget::~AdminMainWidget()
{
    delete ui;
}
