#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int Database::createDB(const char* s) {
    sqlite3* DB;                                                                    //deklaracja wskaŸnika na obiekt bazy danych SQLite
    int exit = sqlite3_open(s, &DB);                                                //próba otwaracia bazy danych; utworzenie je¿eli nie istnieje
    sqlite3_close(DB);                                                              //zamkniêcie bd aby unikn¹æ wycieków pamiêci
    return exit;
}

int Database::createTable(const char* s) {
    sqlite3* DB;
    std::string sql = "CREATE TABLE IF NOT EXISTS CARS_SPECIFICATIONS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "BRAND VARCHAR(255),"
        "MODEL VARCHAR(255),"
        "POWER_HP INT,"
        "CAPACITY_L INT,"
        "ENGINE VARCHAR(255),"
        "TYPE VARCHAR(255),"
        "FUEL VARCHAR(255),"
        "CONSUMPTION_L_PER_100KM FLOAT,"
        "PRODUCTION_YEAR INT,"
        "NUMBER_OF_DOORS INT,"
        "VERSION VARCHAR(255));";

    int exit = sqlite3_open(s, &DB);
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);                      //wykonanie polecenia sql
    if (exit != SQLITE_OK) {
        std::cerr << "Error Creating Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    sqlite3_close(DB);
    return exit;
}


int Database::insertData(const QString& dbPath, const QString& brand, const QString& model, const QString& powerHp,
    const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
    const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
    const QString& version) {
    sqlite3* db;
    if (sqlite3_open(dbPath.toStdString().c_str(), &db) != SQLITE_OK) {
        qDebug() << "Cannot open database: " << sqlite3_errmsg(db);
        return -1;
    }

    const char* sql = "INSERT INTO CARS_SPECIFICATIONS (BRAND, MODEL, "
        "POWER_HP, CAPACITY_L, ENGINE, TYPE, FUEL, CONSUMPTION_L_PER_100KM, "
        "PRODUCTION_YEAR, NUMBER_OF_DOORS, VERSION) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;                                                                     //Deklaracja wskaŸnika na strukturê do zarz¹dzania zapytaniem przygotowanym
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {                     //Przygotowanie zapytania SQL do wykonania
        qDebug() << "Failed to prepare statement: " << sqlite3_errmsg(db);
        sqlite3_close(db);
        return -1;
    }

    // Przypisanie wartoœci do poszczególnych parametrów zapytania SQL
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, brand.toStdString().c_str(), -1, SQLITE_TRANSIENT);          // -1 odpowiada sa obliczenie d³ugoœci zmiennej
    sqlite3_bind_text(stmt, 2, model.toStdString().c_str(), -1, SQLITE_TRANSIENT);          //SQLITE_TRANSIENT to funkcja która mówi, ¿eby SQLite wykona³ kopiê danych. Odpornoœæ na zmiany w trakcie
    sqlite3_bind_text(stmt, 3, powerHp.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, capacityL.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, engine.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, type.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, fuel.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, consumptionLPer100Km.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, productionYear.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, numberOfDoors.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 11, version.toStdString().c_str(), -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);                                                        //Wykonanie zapytania
    if (result != SQLITE_DONE) {
        qDebug() << "Error inserting data: " << sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_finalize(stmt);                                                                 //Zakoñczenie pracy ze zmienn¹ stmt
    sqlite3_close(db);
    return 0;
}

int Database::updateData(const QString& dbPath, int id, const QString& brand, const QString& model, const QString& powerHp,
    const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
    const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
    const QString& version) {
    sqlite3* db;
    sqlite3_open(dbPath.toStdString().c_str(), &db);

    const char* sql = "UPDATE CARS_SPECIFICATIONS SET BRAND = ?, "
        "MODEL = ?, POWER_HP = ?, CAPACITY_L = ?, ENGINE = ?, TYPE = ?, "
        "FUEL = ?, CONSUMPTION_L_PER_100KM = ?, PRODUCTION_YEAR = ?, "
        "NUMBER_OF_DOORS = ?, VERSION = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, brand.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, model.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, powerHp.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, capacityL.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, engine.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, type.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, fuel.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, consumptionLPer100Km.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, productionYear.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, numberOfDoors.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 11, version.toStdString().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 12, id);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        qDebug() << "Error updating data: " << sqlite3_errmsg(db);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result == SQLITE_DONE ? 0 : -1;
}

int Database::deleteData(const QString& dbPath, int id) {
    sqlite3* db;
    sqlite3_open(dbPath.toStdString().c_str(), &db);

    const char* sql = "DELETE FROM CARS_SPECIFICATIONS WHERE ID = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);                                                          // Powi¹zanie ID rekordu z parametrem zapytania

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        qDebug() << "Error deleting data: " << sqlite3_errmsg(db);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result == SQLITE_DONE ? 0 : -1;
}


QSqlQueryModel* Database::getCarSpecificationsModel(const char* s) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "ConnectionName");
    db.setDatabaseName(s);
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError().text();
        return nullptr;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query("SELECT * FROM CARS_SPECIFICATIONS", db);
    model->setQuery(query);

    db.close();                                                                             // Zamkniêcie bazy danych po zakoñczeniu zapytania
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);                          // Usuniêcie identyfikatora po³¹czenia
    return model;
}

QString Database::getCarSpecificationsQuery(const QString& dbPath) {
    return "SELECT * FROM CARS_SPECIFICATIONS";
}

QSqlQueryModel* Database::selectFilteredData(const QString& dbPath, const QString& brand, const QString& model, const QString& powerHp,
    const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
    const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
    const QString& version) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError().text();
        return nullptr;
    }

    QSqlQueryModel* qmodel = new QSqlQueryModel();
    QSqlQuery query(db);
    QString sql = "SELECT * FROM CARS_SPECIFICATIONS WHERE "
        "BRAND LIKE :brand AND MODEL LIKE :model AND POWER_HP LIKE :powerHp AND "
        "CAPACITY_L LIKE :capacityL AND ENGINE LIKE :engine AND TYPE LIKE :type AND "
        "FUEL LIKE :fuel AND CONSUMPTION_L_PER_100KM LIKE :consumptionLPer100Km AND "
        "PRODUCTION_YEAR LIKE :productionYear AND NUMBER_OF_DOORS LIKE :numberOfDoors AND "
        "VERSION LIKE :version;";

    query.prepare(sql);
    query.bindValue(":brand", '%' + brand + '%');
    query.bindValue(":model", '%' + model + '%');
    query.bindValue(":powerHp", powerHp.isEmpty() ? "%%" : '%' + powerHp + '%');
    query.bindValue(":capacityL", capacityL.isEmpty() ? "%%" : '%' + capacityL + '%');
    query.bindValue(":engine", engine.isEmpty() ? "%%" : '%' + engine + '%');
    query.bindValue(":type", type.isEmpty() ? "%%" : '%' + type + '%');
    query.bindValue(":fuel", fuel.isEmpty() ? "%%" : '%' + fuel + '%');
    query.bindValue(":consumptionLPer100Km", consumptionLPer100Km.isEmpty() ? "%%" : '%' + consumptionLPer100Km + '%');
    query.bindValue(":productionYear", productionYear.isEmpty() ? "%%" : '%' + productionYear + '%');
    query.bindValue(":numberOfDoors", numberOfDoors.isEmpty() ? "%%" : '%' + numberOfDoors + '%');
    query.bindValue(":version", version.isEmpty() ? "%%" : '%' + version + '%');
    query.exec();

    qmodel->setQuery(query);
    db.close();

    return qmodel;
}