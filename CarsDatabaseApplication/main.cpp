#include "CarsDatabaseApplication.h"
#include <QtWidgets/QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    Database DB_object;
    const char* dir = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";
    sqlite3* DB;

    DB_object.createDB(dir);
    DB_object.createTable(dir);
    DB_object.insertData(dir);

  


    QApplication a(argc, argv);
    CarsDatabaseApplication w;

    w.setWindowIcon(QIcon("C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\car_icon.ico"));

    w.setFixedSize(991, 658);

    w.show();
    return a.exec();
}
