#include "room.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

bool room::reserveRoom(int roomId, int userId, int day, int month, int year, int day2, int month2, int year2)
{
    static dbManagement* dbManage = dbManagement::getInstance();

    dbManage->openDB();

    const char* sql = "UPDATE rooms SET reserved=1, userId=? WHERE roomId=? ;";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);

    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare statement, " << sqlite3_errmsg(dbManage->db) << ", " << sqlite3_errcode(dbManage->db) << endl;
    }
    else
        cout << "DONE prepare statement reservee" << endl;


    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_int(stmt, 2, roomId);

    dbManage->rc = sqlite3_step(stmt);

    if (dbManage->rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(dbManage->db) << endl;
        sqlite3_finalize(stmt);
        dbManage->closeDB();
        return false;
    }
    else
    {
        cout << "DONE execute statement" << endl;
        bool isDateReserved=reserveRoomDate(roomId, day,  month,  year, day2,  month2, year2);
        if (isDateReserved)
        {
            sqlite3_finalize(stmt);
            dbManage->closeDB();

            incrementUserVisits(userId);
            return true;
        }
        else
        {
            sqlite3_finalize(stmt);
            dbManage->closeDB();
            return false;
        }
    }

}

bool room::reserveRoomDate(int roomId, int day, int month, int year, int day2, int month2, int year2)
{
    static dbManagement* dbManage = dbManagement::getInstance();
    dbManage->openDB();

    const char* sql = "UPDATE rooms SET StartDay=? ,StartMonth=? ,StartYear=? ,EndDay=? ,EndMonth=? ,EndYear=?  WHERE roomId=? ;";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);

    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare statement, " << sqlite3_errmsg(dbManage->db) << ", " << sqlite3_errcode(dbManage->db) << endl;
    }
    else
        cout << "DONE prepare statement reservee" << endl;

    sqlite3_bind_int(stmt, 1, day);
    sqlite3_bind_int(stmt, 2, month);
    sqlite3_bind_int(stmt, 3, year);
    sqlite3_bind_int(stmt, 4, day2);
    sqlite3_bind_int(stmt, 5, month2);
    sqlite3_bind_int(stmt, 6, year2);
    sqlite3_bind_int(stmt, 7, roomId);

    dbManage->rc = sqlite3_step(stmt);

    if (dbManage->rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(dbManage->db) << endl;
        sqlite3_finalize(stmt);
        dbManage->closeDB();
        return false;
    }
    else
    {
        cout << "DONE execute statement" << endl;

        sqlite3_finalize(stmt);
        dbManage->closeDB();
        return true;
    }
}

int room::getUserVisits(int userID)
{
    static dbManagement* dbManage = dbManagement::getInstance();
    dbManage->openDB();
    const char* sql = "SELECT visits FROM users WHERE userId=?";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare select visits statement" << endl;
    }
    else
        cout << "Done prepare select visits statement" << endl;

    sqlite3_bind_int(stmt, 1, userID);
    int visits=-1;

    if ((dbManage->rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        visits = sqlite3_column_int(stmt, 0);
        cout << "USER visits is " << visits << endl;
        sqlite3_finalize(stmt);
    dbManage->closeDB();
        return visits;
    }
    sqlite3_finalize(stmt);
    dbManage->closeDB();
    return -1;
}

void room::incrementUserVisits( int userID)
{
    int visits = getUserVisits(userID);

    static dbManagement* dbManage = dbManagement::getInstance();
    dbManage->openDB();
    
    visits += 1;

    const char* sql = "UPDATE users SET visits=? WHERE userId=?";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);
    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare update visits statement" << endl;
    }
    else
        cout << "Done prepare update visits statement" << endl;

    sqlite3_bind_int(stmt, 1, visits);
    sqlite3_bind_int(stmt, 2, userID);

    dbManage->rc = sqlite3_step(stmt);

    if (dbManage->rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(dbManage->db) << endl;
    }
    else
    {
        cout << "DONE execute statement" << endl;
    }

    sqlite3_finalize(stmt);
    dbManage->closeDB();

    getUserVisits(userID);
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

void room::clearRoom(int roomId)
{
    static dbManagement* dbManage = dbManagement::getInstance();

    dbManage->openDB();

    const char* sql = "UPDATE rooms SET StartDay=0 ,StartMonth=0 ,StartYear=0 ,EndDay=0 ,EndMonth=0 ,EndYear=0,reserved=0  WHERE roomId=? ;";
    sqlite3_stmt* stmt;
    dbManage->rc = sqlite3_prepare_v2(dbManage->db, sql, -1, &stmt, nullptr);

    if (dbManage->rc != SQLITE_OK)
    {
        cout << "Can't prepare statement, " << sqlite3_errmsg(dbManage->db) << ", " << sqlite3_errcode(dbManage->db) << endl;
    }
    else
        cout << "DONE prepare statement reservee" << endl;

    sqlite3_bind_int(stmt, 1, roomId);
    dbManage->rc = sqlite3_step(stmt);

    if (dbManage->rc != SQLITE_DONE)
    {
        cout << "Can't execute statement " << sqlite3_errmsg(dbManage->db) << endl;
    }
    else
    {
        cout << "DONE execute statement" << endl;

    }

	userId = -1;

    sqlite3_finalize(stmt);
    dbManage->closeDB();
}