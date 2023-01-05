#pragma once

#include <QDialog>

namespace Ui {
class punishmentDialog;
}

class punishmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit punishmentDialog(QWidget *parent = nullptr);
    ~punishmentDialog();

private:
    Ui::punishmentDialog *ui;
};

