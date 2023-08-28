#pragma once

using namespace std;
#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

class dbManagement
{
public:
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	void openDB();
	void closeDB();
	void validateTableCreation(int rc);
    void createTable();
	void createDB();
	bool validateUser(string em, string pass);
	bool detectDuplicateEmail(string em, string pass);
	dbManagement();
};

