#include "doubleRG.h"
using namespace std;

#include <iostream>
#include <string>
#include "dbManagement.h"
#include "sqlite/sqlite3.h"

void doubleRG::displayAvailableRooms(vector<int>& roomsId)
{
    dbManagement* dbManage = dbManage->getInstance();

    const char* sql = "SELECT * FROM rooms WHERE reserved !=1 AND size = 2 AND view = 'garden';";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare select double garden rooms statement" << endl;
    }
    else
        cout << "Done prepare select double garden rooms statement" << endl;

   
    if (dbManage->rc != SQLITE_ROW)
    {
        cout << "No " << this->size << " rooms with " << this->view << " view available currently" << endl;
    }
    else
    {
        cout << "Garden double Rooms available are:" << endl;
        while ((dbManage->rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            int building = sqlite3_column_int(stmt, 1);
            int floor = sqlite3_column_int(stmt, 2);

            cout << "room id: " << id << ", " << "building#: " << building << ", " << "floor#: " << floor << endl;
            roomsId.push_back(id);
        }
    }
    sqlite3_finalize(stmt);
}
