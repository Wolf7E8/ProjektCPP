#include "CarsDatabaseApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Database DB_object;
    const char* dir = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";
    sqlite3* DB;

    DB_object.createDB(dir);
    DB_object.createTable(dir);


    QApplication a(argc, argv);
    CarsDatabaseApplication w;
    w.show();
    return a.exec();
}
