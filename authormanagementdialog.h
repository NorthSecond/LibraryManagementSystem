#pragma once

#include <QDialog>

namespace Ui {
class AuthorManageMentDialog;
}

class AuthorManageMentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorManageMentDialog(QWidget *parent = nullptr);
    ~AuthorManageMentDialog();

private:
    Ui::AuthorManageMentDialog *ui;
};

