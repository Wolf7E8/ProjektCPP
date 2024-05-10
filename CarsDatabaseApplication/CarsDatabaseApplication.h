#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CarsDatabaseApplication.h"
#include "Database.h"
#include <sqlite3.h>
#include <QSqlQueryModel>
#include <QTableView>

class CarsDatabaseApplication : public QMainWindow
{
    Q_OBJECT

public:
    CarsDatabaseApplication(QWidget *parent = nullptr);
    ~CarsDatabaseApplication();

private slots: // Dodaj sekcjê slots, jeœli jeszcze nie istnieje
    void refreshData(); // Deklaracja slotu do odœwie¿ania danych

private:
    Ui::CarsDatabaseApplicationClass ui;


};
