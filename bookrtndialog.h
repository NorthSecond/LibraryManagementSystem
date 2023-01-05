#pragma once

#include <QDialog>

namespace Ui {
class BookRtnDialog;
}

class BookRtnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookRtnDialog(QWidget *parent = nullptr);
    ~BookRtnDialog();

private:
    Ui::BookRtnDialog *ui;
};

