#include "tripleRB.h"
using namespace std;

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

void tripleRB::getRooms()
{
    const char* sql = "SELECT * FROM rooms WHERE reserved = 0 AND size = 3 AND view = 'sea';";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Can't prepare select triple beach rooms statement" << endl;
    }
    else
        cout << "Done prepare select triple beach rooms statement" << endl;

    cout << "Beach triple Rooms available are:" << endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int building = sqlite3_column_int(stmt, 1);
        int floor = sqlite3_column_int(stmt, 2);

        cout << "room id: " << id << ", " << "building#: " << building << ", " << "floor#: " << floor << endl;
    }
}