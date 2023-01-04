#pragma once

#include <QMainWindow>
#include <QMessagebox>

#include "adminmainwidget.h"
#include "userinfo.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

protected:
    bool eventFilter(QObject* obj, QEvent* e);
    
private:
    Ui::AdminWindow *ui;
	unsigned long long id;
    

public slots:
    void getUserInfo(unsigned long long id);

private slots:
    void on_change_btn_clicked();
    void on_exit_btn_clicked();
};

