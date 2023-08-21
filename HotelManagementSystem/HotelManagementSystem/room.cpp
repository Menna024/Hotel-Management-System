#include "room.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

bool room::reserveRoom(int roomId, int userId, int day, int month, int year, int day2, int month2, int year2)
{
    const char* sql = "UPDATE rooms SET reserved=1, userId=?, StartDay=? ,StartMonth=? ,StartYear=? ,EndDay=? ,EndMonth=? ,EndYear=?  WHERE roomId=? ;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Can't prepare statement, " << sqlite3_errmsg(db) << ", " << sqlite3_errcode(db) << endl;
    }
    else
        cout << "DONE prepare statement reservee" << endl;


    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_int(stmt, 2, day);
    sqlite3_bind_int(stmt, 3, month);
    sqlite3_bind_int(stmt, 4, year);
    sqlite3_bind_int(stmt, 5, day2);
    sqlite3_bind_int(stmt, 6, month2);
    sqlite3_bind_int(stmt, 7, year2);

    sqlite3_bind_int(stmt, 8, roomId);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(db) << endl;
        return false;
    }
    else
    {
        cout << "DONE execute statement" << endl;
        return true;
    }
}

bool room::setArrivalDate(int day, int month, int year)
{
	dayFrom = day;
	monthFrom = month;
	yearFrom = year;
	return true;
}

bool room::setDepartureDate(int day, int month, int year)
{
	dayTill= day;
	monthTill = month;
	yearTill= year;
	return true;
}

bool room::clearRoom()
{
	

	userId = -1;

	return true;
}