#include "user.h"
#include "dbManagement.h"


void user:: addUser(string email,string password,string fName,string sName,int age)
{
   dbManagement* dbManage = dbManage->getInstance();
    const char* sql = "INSERT INTO users (email,password,firstName,secondName,age,visits) VALUES (?,?,?,?,?,0);";

    sqlite3_stmt* stmt;
    dbManage->rc= sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare statement, " << sqlite3_errmsg(dbManage->db) << ", " << sqlite3_errcode(dbManage->db) << endl;
    }
    else
        cout << "DONE prepare statement" << endl;


    const char* userEm = email.c_str();
    const char* userPass = password.c_str();
    const char* userFName = fName.c_str();
    const char* userSName = sName.c_str();

    sqlite3_bind_text(stmt, 1, userEm, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, userPass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, userFName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, userSName, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, age);

    dbManage->rc = sqlite3_step(stmt);
    if (dbManage->rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(dbManage->db) << endl;
    }
    else
        cout << "DONE execute statement" << endl;

    sqlite3_finalize(stmt);
}

void user:: getUserId(string em, string pass)
{
    dbManagement* dbManage = dbManage->getInstance();

    const char* sql = "SELECT * FROM users WHERE email = ? AND password = ?";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare select users statement" << endl;
    }
    else
        cout << "Done prepare select users statement" << endl;

    dbManage->rc = sqlite3_bind_text(stmt, 1, em.c_str(), -1, SQLITE_STATIC);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't bind email" << endl;
    }
    else
        cout << "Done bind email" << endl;

    dbManage->rc = sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_STATIC);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't bind pass" << endl;
    }
    else
        cout << "Done bind pass" << endl;

    if ((dbManage->rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        currentUserId = sqlite3_column_int(stmt, 0);
        cout << "USER ID IS " << currentUserId << endl;
    }
    sqlite3_finalize(stmt);
    
}
