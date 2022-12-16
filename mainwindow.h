// Main Window
// use to login the system

#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QString>

#include "databaseRepository.h"
#include "adminmainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const unsigned int window_width = 640;
    const unsigned int window_height = 480;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* username_lbl;
    QLabel* passwd_lbl;
    QLabel* identity_lbl;

    QLineEdit* username_edit;
    QLineEdit* passwd_edit;
    QComboBox* identity_box;

    QPushButton* login_btn;
    QPushButton* exit_btn;

    DatabaseRepository db;
public slots:
    void login_btn_pushed();
    void exit_btn_pushed();
};
