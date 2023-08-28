#include "tripleRG.h"

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

void tripleRG::displayAvailableRooms()
{
    dbManage.openDB();

    const char* sql = "SELECT * FROM rooms WHERE reserved!=1 AND size = 3 AND view = 'garden';";
    sqlite3_stmt* stmt;
    dbManage.rc = sqlite3_prepare_v2(dbManage.db, sql, -1, &stmt, nullptr);
    if (dbManage.rc != SQLITE_OK)
    {
        cout << "Can't prepare select triple garden rooms statement" << endl;
    }
    else
        cout << "Done prepare select triple garden rooms statement" << endl;


    if ((dbManage.rc = sqlite3_step(stmt)) != SQLITE_ROW)
    {
        cout << "No " << this->size << " rooms with " << this->view << " view available currently" << endl;
    }
    else
    {
        cout << "Garden triple Rooms available are:" << endl;
        while ((dbManage.rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            int building = sqlite3_column_int(stmt, 1);
            int floor = sqlite3_column_int(stmt, 2);

            cout << "room id: " << id << ", " << "building#: " << building << ", " << "floor#: " << floor << endl;
        }
    }
    sqlite3_finalize(stmt);
    dbManage.closeDB();
}