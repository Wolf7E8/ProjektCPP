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
        "Brand           VARCHAR(255),"
        "Model           VARCHAR(255),"
        "Power           INT,"
        "Capacity        INT,"
        "Engine          VARCHAR(255),"
        "Type            VARCHAR(255),"
        "Fuel            VARCHAR(255),"
        "Consumption     FLOAT,"
        "ProductionYear  INT,"
        "NumberOfDoors   INT,"
        "Version         VARCHAR(255) );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Create Table" << std::endl;
            sqlite3_free(messaggeError);
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
    return 0;
}
