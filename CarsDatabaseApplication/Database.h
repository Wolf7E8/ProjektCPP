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
	static int insertData(const QString& dbPath, const QString& brand, const QString& model, const QString& powerHp,
		const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
		const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
		const QString& version);
	static int updateData(const QString& dbPath, int id, const QString& brand, const QString& model, const QString& powerHp,
		const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
		const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
		const QString& version);
	static int deleteData(const QString& dbPath, int id);
	static int selectData(const char* s);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);

	static QSqlQueryModel* getCarSpecificationsModel(const char* s);
	static QString getCarSpecificationsQuery(const QString& dbPath);
	static QSqlQueryModel* selectFilteredData(const QString& dbPath, const QString& brand, const QString& model, const QString& powerHp,
		const QString& capacityL, const QString& engine, const QString& type, const QString& fuel,
		const QString& consumptionLPer100Km, const QString& productionYear, const QString& numberOfDoors,
		const QString& version);
};

