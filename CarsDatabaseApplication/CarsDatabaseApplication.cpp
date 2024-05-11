#include "CarsDatabaseApplication.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "Database.h"


CarsDatabaseApplication::CarsDatabaseApplication(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);

    refreshData();

    connect(ui.refresh, &QPushButton::clicked, this, &CarsDatabaseApplication::refreshData);
    connect(ui.addButton, &QPushButton::clicked, this, &CarsDatabaseApplication::addData);
    connect(ui.deleteButton, &QPushButton::clicked, this, &CarsDatabaseApplication::deleteData);
    connect(ui.updateButton, &QPushButton::clicked, this, &CarsDatabaseApplication::updateData);
    connect(ui.selectButton, &QPushButton::clicked, this, &CarsDatabaseApplication::selectData);
    connect(ui.searchButton, &QPushButton::clicked, this, &CarsDatabaseApplication::searchData);
    connect(ui.sortButton, &QPushButton::clicked, this, &CarsDatabaseApplication::sortProductionYear);
}

CarsDatabaseApplication::~CarsDatabaseApplication() {

    auto model = ui.output_table->model();
    ui.output_table->setModel(nullptr);
    delete model;

    QSqlDatabase::removeDatabase("ConnectionName");
}

void CarsDatabaseApplication::refreshData() {
    auto oldModel = dynamic_cast<QSqlQueryModel*>(ui.output_table->model());
    if (oldModel) {
        delete oldModel;
    }

    QSqlQueryModel* newModel = Database::getCarSpecificationsModel("C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db");
    if (newModel) {
        ui.output_table->setModel(newModel);
    }
    else {
        qDebug() << "Failed to load data!";
    }
}

void CarsDatabaseApplication::addData() {
    QString brand = ui.input_BRAND->toPlainText();
    QString model = ui.input_MODEL->toPlainText();
    QString powerHp = ui.input_POWER->toPlainText();
    QString capacityL = ui.input_CAPACITY->toPlainText();
    QString engine = ui.input_ENGINE->toPlainText();
    QString type = ui.input_TYPE->toPlainText();
    QString fuel = ui.input_FUEL->toPlainText();
    QString consumptionLPer100Km = ui.input_CONSUMPTION->toPlainText();
    QString productionYear = ui.input_PY->toPlainText();
    QString numberOfDoors = ui.input_NoD->toPlainText();
    QString version = ui.input_VERSION->toPlainText();

    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";

    int result = Database::insertData(dbPath, brand, model, powerHp, capacityL, engine, type, fuel, consumptionLPer100Km, productionYear, numberOfDoors, version);
    if (result == 0) {
        qDebug() << "Data inserted successfully";
    }
    else {
        qDebug() << "Failed to insert data";
    }

    refreshData();
}

void CarsDatabaseApplication::deleteData() {
    int id = ui.input_ID->toPlainText().toInt();
    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";

    int result = Database::deleteData(dbPath, id);
    if (result == 0) {
        qDebug() << "Record deleted successfully";
    }
    else {
        qDebug() << "Failed to delete record";
    }

    refreshData();
}

void CarsDatabaseApplication::updateData() {
    // Konwersja i pobranie wartoœci z interfejsu u¿ytkownika
    int id = ui.input_ID->toPlainText().toInt();
    QString brand = ui.input_BRAND->toPlainText();
    QString model = ui.input_MODEL->toPlainText();
    QString powerHp = ui.input_POWER->toPlainText();
    QString capacityL = ui.input_CAPACITY->toPlainText();
    QString engine = ui.input_ENGINE->toPlainText();
    QString type = ui.input_TYPE->toPlainText();
    QString fuel = ui.input_FUEL->toPlainText();
    QString consumptionLPer100Km = ui.input_CONSUMPTION->toPlainText();
    QString productionYear = ui.input_PY->toPlainText();
    QString numberOfDoors = ui.input_NoD->toPlainText();
    QString version = ui.input_VERSION->toPlainText();

    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";

    int result = Database::updateData(dbPath, id, brand, model, powerHp, capacityL, engine, type, fuel,
        consumptionLPer100Km, productionYear, numberOfDoors, version);
    if (result == 0) {
        qDebug() << "Record updated successfully";
    }
    else {
        qDebug() << "Failed to update record";
    }

    refreshData();
}

void CarsDatabaseApplication::selectData() {
    QString brand = ui.input_BRAND->toPlainText();
    QString model = ui.input_MODEL->toPlainText();
    QString powerHp = ui.input_POWER->toPlainText();
    QString capacityL = ui.input_CAPACITY->toPlainText();
    QString engine = ui.input_ENGINE->toPlainText();
    QString type = ui.input_TYPE->toPlainText();
    QString fuel = ui.input_FUEL->toPlainText();
    QString consumptionLPer100Km = ui.input_CONSUMPTION->toPlainText();
    QString productionYear = ui.input_PY->toPlainText();
    QString numberOfDoors = ui.input_NoD->toPlainText();
    QString version = ui.input_VERSION->toPlainText();

    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";
    QSqlQueryModel* qmodel = Database::selectFilteredData(dbPath, brand, model, powerHp, capacityL, engine, type, fuel,
        consumptionLPer100Km, productionYear, numberOfDoors, version);
    if (qmodel) {
        ui.output_table->setModel(qmodel);
    }
    else {
        qDebug() << "Failed to load filtered data!";
    }
}

void CarsDatabaseApplication::searchData() {
    QString brand = ui.input_BRAND_2->toPlainText();
    QString model = ui.input_MODEL_2->toPlainText();
    QString powerHp = ui.input_POWER_2->toPlainText();
    QString capacityL = ui.input_CAPACITY_2->toPlainText();
    QString engine = ui.input_ENGINE_2->toPlainText();
    QString type = ui.input_TYPE_2->toPlainText();
    QString fuel = ui.input_FUEL_2->toPlainText();
    QString consumptionLPer100Km = ui.input_CONSUMPTION_2->toPlainText();
    QString productionYear = ui.input_PY_2->toPlainText();
    QString numberOfDoors = ui.input_NoD_2->toPlainText();
    QString version = ui.input_VERSION_2->toPlainText();

    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    QString sql = "SELECT COUNT(*) FROM CARS_SPECIFICATIONS WHERE "
        "(:brand IS NULL OR BRAND = :brand) AND "
        "(:model IS NULL OR MODEL = :model) AND "
        "(:powerHp IS NULL OR POWER_HP = :powerHp) AND "
        "(:capacityL IS NULL OR CAPACITY_L = :capacityL) AND "
        "(:engine IS NULL OR ENGINE = :engine) AND "
        "(:type IS NULL OR TYPE = :type) AND "
        "(:fuel IS NULL OR FUEL = :fuel) AND "
        "(:consumptionLPer100Km IS NULL OR CONSUMPTION_L_PER_100KM = :consumptionLPer100Km) AND "
        "(:productionYear IS NULL OR PRODUCTION_YEAR = :productionYear) AND "
        "(:numberOfDoors IS NULL OR NUMBER_OF_DOORS = :numberOfDoors) AND "
        "(:version IS NULL OR VERSION = :version);";

    query.prepare(sql);
    query.bindValue(":brand", brand.isEmpty() ? QVariant(QVariant::String) : brand);
    query.bindValue(":model", model.isEmpty() ? QVariant(QVariant::String) : model);
    query.bindValue(":powerHp", powerHp.isEmpty() ? QVariant(QVariant::String) : powerHp);
    query.bindValue(":capacityL", capacityL.isEmpty() ? QVariant(QVariant::String) : capacityL);
    query.bindValue(":engine", engine.isEmpty() ? QVariant(QVariant::String) : engine);
    query.bindValue(":type", type.isEmpty() ? QVariant(QVariant::String) : type);
    query.bindValue(":fuel", fuel.isEmpty() ? QVariant(QVariant::String) : fuel);
    query.bindValue(":consumptionLPer100Km", consumptionLPer100Km.isEmpty() ? QVariant(QVariant::String) : consumptionLPer100Km);
    query.bindValue(":productionYear", productionYear.isEmpty() ? QVariant(QVariant::String) : productionYear);
    query.bindValue(":numberOfDoors", numberOfDoors.isEmpty() ? QVariant(QVariant::String) : numberOfDoors);
    query.bindValue(":version", version.isEmpty() ? QVariant(QVariant::String) : version);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        db.close();
        return;
    }

    int count = 0;
    if (query.next()) {
        count = query.value(0).toInt();
    }

    QSqlQuery totalQuery("SELECT COUNT(*) FROM CARS_SPECIFICATIONS", db);
    int totalCount = 0;
    if (totalQuery.next()) {
        totalCount = totalQuery.value(0).toInt();
    }

    double percentage = totalCount == 0 ? 0 : (100.0 * count / totalCount);

    ui.lcdNumber_amount->display(count);
    ui.lcdNumber_percent->display(percentage);

    db.close();
}

void CarsDatabaseApplication::sortProductionYear() {
    // Tworzenie po³¹czenia z baz¹ danych
    QString dbPath = "C:\\Users\\grzeg\\Desktop\\Visual_Studio_2022\\ProjektCPP\\CARS.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError().text();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel;                                                         // Tworzenie nowego modelu
    model->setQuery("SELECT * FROM CARS_SPECIFICATIONS ORDER BY PRODUCTION_YEAR ASC", db);              // Wykonanie zapytania SQL

    if (model->lastError().isValid()) {
        qDebug() << "Error sorting data:" << model->lastError().text();
    }
    else {
        qDebug() << "Data sorted successfully.";
        ui.output_table->setModel(model);                                                               // Ustawienie modelu dla widoku tabeli
    }

    db.close();                                                                                         // Zamkniêcie po³¹czenia z baz¹ danych
}
