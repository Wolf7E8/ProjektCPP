#include "CarsDatabaseApplication.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>


CarsDatabaseApplication::CarsDatabaseApplication(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);

    refreshData(); // U¿yj funkcji odœwie¿enia przy inicjalizacji

    connect(ui.refresh, &QPushButton::clicked, this, &CarsDatabaseApplication::refreshData);
}

CarsDatabaseApplication::~CarsDatabaseApplication() {
    // Usuñ model, jeœli istnieje, przed zamkniêciem aplikacji
    auto model = ui.output_table->model();
    ui.output_table->setModel(nullptr);
    delete model;

    QSqlDatabase::removeDatabase("ConnectionName"); // Upewnij siê, ¿e po³¹czenie jest zamkniête
}

void CarsDatabaseApplication::refreshData() {
    auto oldModel = dynamic_cast<QSqlQueryModel*>(ui.output_table->model());
    if (oldModel) {
        delete oldModel; // Usuñ stary model
    }

    QSqlQueryModel* newModel = Database::getCarSpecificationsModel("C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db");
    if (newModel) {
        ui.output_table->setModel(newModel);
    }
    else {
        qDebug() << "Failed to load data!";
    }
}
