#pragma once

#include <QWidget>
#include <QGraphicsView>

namespace Ui {
class AdminMainWidget;
}

class AdminMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainWidget(QWidget *parent = nullptr);
	explicit AdminMainWidget(QGraphicsView* view, QString name, QWidget* parent = nullptr);
	explicit AdminMainWidget(QString name, QWidget* parent = nullptr);
    
    ~AdminMainWidget();
	void setGrap(QGraphicsView* view);
	void setNameLbl(QString name);

private:
    Ui::AdminMainWidget *ui;
};

