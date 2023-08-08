#pragma once
#include "poolRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class tripleRP :
    public poolRoom
{
public:
    string size = "triple";

    sqlite3* db;
    char* zErrMsg = 0;
    int rc = sqlite3_open("hotel.db", &db);

    void getRooms();
};

