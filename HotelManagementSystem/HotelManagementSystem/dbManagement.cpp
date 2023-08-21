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
        "reserved INT NOT NULL,userId INTEGER,  StartDay INT ,StartMonth INT ,StartYear INT ,EndDay INT ,EndMonth INT ,EndYear INT);", callback, 0, &zErrMsg);
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
    return isUserFound;
} //For signup verification, if user wants to make an account with already existing email

