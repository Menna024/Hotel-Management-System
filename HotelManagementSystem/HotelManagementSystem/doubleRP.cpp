#include "doubleRP.h"

using namespace std;

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

void doubleRP::displayAvailableRooms(vector<int>& roomsId)
{
    dbManage.openDB();
    const char* sql = "SELECT * FROM rooms WHERE reserved !=1 AND size = 2 AND view = 'pool';";
    sqlite3_stmt* stmt;
    dbManage.rc = sqlite3_prepare_v2(dbManage.db, sql, -1, &stmt, nullptr);
    if (dbManage.rc != SQLITE_OK)
    {
        cout << "Can't prepare select double pool rooms statement" << endl;
    }
    else
        cout << "Done prepare select double pool rooms statement" << endl;

    if ((dbManage.rc = sqlite3_step(stmt)) != SQLITE_ROW)
    {
        cout << "No " << this->size << " rooms with " << this->view << " view available currently" << endl;
    }
    else
    {
        cout << "Pool double Rooms available are:" << endl;
        while ((dbManage.rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            int building = sqlite3_column_int(stmt, 1);
            int floor = sqlite3_column_int(stmt, 2);

            cout << "room id: " << id << ", " << "building#: " << building << ", " << "floor#: " << floor << endl;
            roomsId.push_back(id);
        }
    }
    sqlite3_finalize(stmt);
    dbManage.closeDB();

}
