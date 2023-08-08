#pragma once

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"


class dbManagement
{
public:
	sqlite3* db;
	char* zErrMsg = 0;
	int rc = sqlite3_open("hotel.db", &db);

	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	void validateTableCreation(int rc);
    void createTable();
	void createDB();
	dbManagement();
};

