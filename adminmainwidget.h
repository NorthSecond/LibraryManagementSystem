#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QEvent>
#include <QMouseEvent>

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

protected:
    virtual void mouseReleaseEvent(QMouseEvent* ev);  // 声明鼠标左键点击事件

signals:
    void clicked(void); // 声明鼠标左击中信号

private:
    Ui::AdminMainWidget *ui;
};

