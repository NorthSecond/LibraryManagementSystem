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
#include "ui_mainwindow.h"
#include "adminwindow.h"
#include "usermainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	QPushButton* login_btn;
	QPushButton* exit_btn;
    
	QLabel* user_label;
	QLabel* password_label;
	QLabel* role_label;
	
	QLineEdit* user_line;
	QLineEdit* password_line;
	QComboBox* role_combo;

signals:
	void sendLoginInfo(unsigned long long id);

private slots:
	void login_btn_pushed();
	void exit_btn_pushed();
};
