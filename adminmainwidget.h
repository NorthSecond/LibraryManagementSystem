#pragma once

#include <QWidget>

namespace Ui {
class AdminMainWidget;
}

class AdminMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainWidget(QWidget *parent = nullptr);
    ~AdminMainWidget();

private:
    Ui::AdminMainWidget *ui;
};

