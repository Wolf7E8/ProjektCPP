#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CarsDatabaseApplication.h"
#include "Database.h"
#include <sqlite3.h>
#include <QSqlQueryModel>

class CarsDatabaseApplication : public QMainWindow
{
    Q_OBJECT

public:
    CarsDatabaseApplication(QWidget *parent = nullptr);
    ~CarsDatabaseApplication();
    void addData();
    void deleteData();
    void updateData();
    void selectData();
    void searchData();

private slots:
    void refreshData();
    void sortProductionYear();


private:
    Ui::CarsDatabaseApplicationClass ui;


};
