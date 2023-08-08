using namespace std;

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "dbManagement.h"

int dbManagement::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void dbManagement::validateTableCreation(int rc)
{
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Table created successfully\n");
    }
}

void dbManagement::createTable()
{
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(userId INTEGER PRIMARY KEY AUTOINCREMENT,"
        "email TEXT NOT NULL, password TEXT NOT NULL,"
        "firstName TEXT NOT NULL,secondName TEXT NOT NULL, "
        "age INT NOT NULL, reservationId INT, visits INT NOT NULL,"
        "ArrivalDate TEXT, DepartureDate TEXT); ", callback, 0, &zErrMsg);
    validateTableCreation(rc);

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS rooms(roomId INTEGER PRIMARY KEY,"
        "building INT NOT NULL, floor INT NOT NULL,"
        "view TEXT NOT NULL,size INT NOT NULL,"
        "reserved INT NOT NULL,userId INTEGER, StartDate TEXT, "
        "EndDate TEXT);", callback, 0, &zErrMsg);
    validateTableCreation(rc);
}

void dbManagement::createDB()
{
    if (rc != SQLITE_OK)
        cout << "NOT OPEN" << endl;
    else
        cout << "Database is OPEN" << endl;

    createTable();
}

dbManagement::dbManagement()
{
    createDB();
}

