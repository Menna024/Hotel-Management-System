#include "user.h"

void user:: getUserId(string em, string pass)
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

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        currentUserId = sqlite3_column_int(stmt, 0);
        cout << "USER ID IS " << currentUserId << endl;
    }
}
