#pragma once

#include <QtWidgets/QMainWindow>
#include "CarsDatabaseApplication.h"
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <exception>

class Database
{
public:
	static int createDB(const char* s);
	static int createTable(const char* s);
	static int insertData(const char* s);
};

