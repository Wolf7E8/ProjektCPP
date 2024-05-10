#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int Database::createDB(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    sqlite3_close(DB);
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
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Creating Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    sqlite3_close(DB);
    return exit;
}

// Implementacje innych funkcji pozostaj¹ bez zmian

int Database::insertData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    std::string sql("INSERT INTO CARS_SPECIFICATIONS (BRAND, MODEL, POWER_HP) VALUES('Volvo', 'x40', 150);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    return 0;
}

int Database::updateData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    std::string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    return 0;
}

int Database::deleteData(const char* s)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);

    std::string sql = "DELETE FROM GRADES;";
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;
}

int Database::selectData(const char* s)     //metoda odpowiadaj¹ca za zdefiniowanie zapytania do bazy danych i wywo³¹nia funkcji wybieraj¹cej
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);
    std::string sql = "SELECT * FROM GRADES;"; //tu nie bêdzie grades

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL); //wywo³ywane odsobno dla ka¿dego wiersza wyniku

    return 0;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }

    std::cout << std::endl;

    return 0;
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

    db.close(); // Zamkniêcie bazy danych po zakoñczeniu zapytania
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection); // Usuniêcie identyfikatora po³¹czenia
    return model;
}

QString Database::getCarSpecificationsQuery(const QString& dbPath) {
    return "SELECT * FROM CARS_SPECIFICATIONS";
}