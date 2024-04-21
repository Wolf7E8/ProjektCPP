#include "Database.h"

int Database::createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

int Database::createTable(const char* s)
{
    sqlite3* DB;

    std::string sql = "CREATE TABLE IF NOT EXISTS CARS_SPECIFICATIONS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "BRAND                      VARCHAR(255),"
        "MODEL                      VARCHAR(255),"
        "POWER_HP                   INT,"
        "CAPACITY_L                 INT,"
        "ENGINE                     VARCHAR(255),"
        "TYPE                       VARCHAR(255),"
        "FUEL                       VARCHAR(255),"
        "CONSUMPTION_L_PER_100KM    FLOAT,"
        "PRODUCTION_YEAR            INT,"
        "NUMBER_OF_DOORS            INT,"
        "VERSION                    VARCHAR(255) );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Create Table" << std::endl;
            sqlite3_free(messageError);
        }
        else
            std::cout << "Table created successfully" << std::endl;
        sqlite3_close(DB);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }

	return 0;
}

int Database::insertData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    std::string sql("INSERT INTO CARS_SPECIFICATIONS (BRAND, MODEL, POWER_HP) VALUES('Kia', 'Ceed', 90);");

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
