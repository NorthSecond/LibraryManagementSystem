#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QMessagebox>

#include "userinfo.h"
#include "databaseRepository.h"
#include "punishinfo.h"

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
	QStandardItemModel* mod;
	QVector<PunishInfo> infos;

private slots:
	void on_searchButton_clicked();
	void on_punishButton_clicked();
	void on_backButton_clicked();
};

