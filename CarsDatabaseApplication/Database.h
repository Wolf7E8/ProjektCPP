#pragma once

#include <QtWidgets/QMainWindow>
#include "CarsDatabaseApplication.h"
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <exception>
#include <QSqlQueryModel>

class Database
{
public:
	static int createDB(const char* s);
	static int createTable(const char* s);
	static int insertData(const char* s);
	static int updateData(const char* s);
	static int deleteData(const char* s);
	static int selectData(const char* s);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);

	static QSqlQueryModel* getCarSpecificationsModel(const char* s);
	static QString getCarSpecificationsQuery(const QString& dbPath);
};

