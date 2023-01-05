#pragma once

#include <QDialog>

namespace Ui {
class changeAdminInfoDialog;
}

class changeAdminInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeAdminInfoDialog(QWidget *parent = nullptr);
    ~changeAdminInfoDialog();

private:
    Ui::changeAdminInfoDialog *ui;
};

