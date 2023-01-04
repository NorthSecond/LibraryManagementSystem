#pragma once

#include <QMainWindow>

namespace Ui {
class userMainWindow;
}

class userMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userMainWindow(QWidget *parent = nullptr);
    ~userMainWindow();

private:
    Ui::userMainWindow *ui;
};

