#pragma once

#include <QDialog>

namespace Ui {
class ReaderAccountDialog;
}

class ReaderAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReaderAccountDialog(QWidget *parent = nullptr);
    ~ReaderAccountDialog();

private:
    Ui::ReaderAccountDialog *ui;
};

