#include "CarsDatabaseApplication.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>


CarsDatabaseApplication::CarsDatabaseApplication(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);

    refreshData(); // U�yj funkcji od�wie�enia przy inicjalizacji

    connect(ui.refresh, &QPushButton::clicked, this, &CarsDatabaseApplication::refreshData);
}

CarsDatabaseApplication::~CarsDatabaseApplication() {
    // Usu� model, je�li istnieje, przed zamkni�ciem aplikacji
    auto model = ui.output_table->model();
    ui.output_table->setModel(nullptr);
    delete model;

    QSqlDatabase::removeDatabase("ConnectionName"); // Upewnij si�, �e po��czenie jest zamkni�te
}

void CarsDatabaseApplication::refreshData() {
    auto oldModel = dynamic_cast<QSqlQueryModel*>(ui.output_table->model());
    if (oldModel) {
        delete oldModel; // Usu� stary model
    }

    QSqlQueryModel* newModel = Database::getCarSpecificationsModel("C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db");
    if (newModel) {
        ui.output_table->setModel(newModel);
    }
    else {
        qDebug() << "Failed to load data!";
    }
}
