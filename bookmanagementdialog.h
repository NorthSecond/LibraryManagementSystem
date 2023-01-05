#pragma once

#include <QDialog>

namespace Ui {
class BookManagementDialog;
}

class BookManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookManagementDialog(QWidget *parent = nullptr);
    ~BookManagementDialog();

private:
    Ui::BookManagementDialog *ui;
};

