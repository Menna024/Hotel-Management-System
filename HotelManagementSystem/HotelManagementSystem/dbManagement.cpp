using namespace std;

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "dbManagement.h"

dbManagement* dbManagement:: getInstance()
{
    if (dbManage == NULL)
    {
        dbManage = new dbManagement();
        return dbManage;
    }
    else
    {
        return dbManage;
    }
}

void dbManagement::openDB()
{
    rc = sqlite3_open("hotel.db", &db);
}

void  dbManagement::closeDB()
{
    sqlite3_close(db);
}

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
  /* if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Table created successfully\n");
    }
    */
}

void dbManagement::createTable()
{
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(userId INTEGER PRIMARY KEY AUTOINCREMENT,"
        "email TEXT NOT NULL, password TEXT NOT NULL,"
        "firstName TEXT NOT NULL,secondName TEXT NOT NULL, "
        "age INTEGER NOT NULL, reservationId INTEGER, visits INTEGER NOT NULL,"
        "ArrivalDate TEXT, DepartureDate TEXT); ", callback, 0, &zErrMsg);
    validateTableCreation(rc);

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS rooms(roomId INTEGER PRIMARY KEY,"
        "building INTEGER NOT NULL, floor INTEGER NOT NULL,"
        "view TEXT NOT NULL,size INTEGER NOT NULL,"
        "reserved INTEGER NOT NULL,userId INTEGER,  StartDay INTEGER ,StartMonth INTEGER ,StartYear INTEGER ,EndDay INTEGER ,EndMonth INTEGER ,EndYear INTEGER, price NUMERIC);", callback, 0, &zErrMsg);
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
    openDB();
    createDB();
}

bool dbManagement::validateUser(string em, string pass)
{
    const char* sql = "SELECT * FROM users WHERE email = ? AND password = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Can't prepare select users statement" << endl;
    }
    else
        cout << "Done prepare select users statement" << endl;

    rc = sqlite3_bind_text(stmt, 1, em.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        cout << "Can't bind email" << endl;
    }
    else
        cout << "Done bind email" << endl;

    rc = sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        cout << "Can't bind pass" << endl;
    }
    else
        cout << "Done bind pass" << endl;

    bool isUserFound = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        isUserFound = true;
    }
    sqlite3_finalize(stmt);

    return isUserFound;

} //For login verification

bool dbManagement::detectDuplicateEmail(string em,string pass)
{
    const char* sql = "SELECT * FROM users WHERE email = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Can't prepare select users statement" << endl;
    }
    else
        cout << "Done prepare select users statement" << endl;

    rc = sqlite3_bind_text(stmt, 1, em.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        cout << "Can't bind email" << endl;
    }
    else
        cout << "Done bind email" << endl;

    bool isUserFound = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        isUserFound = true;
    }

    sqlite3_finalize(stmt);
    return isUserFound;
} //For signup verification, if user wants to make an account with already existing email