#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CarsDatabaseApplication.h"
#include "Database.h"
#include <sqlite3.h>

class CarsDatabaseApplication : public QMainWindow
{
    Q_OBJECT

public:
    CarsDatabaseApplication(QWidget *parent = nullptr);
    ~CarsDatabaseApplication();

private:
    Ui::CarsDatabaseApplicationClass ui;
};
