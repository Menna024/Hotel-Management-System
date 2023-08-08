#pragma once
#include "beachRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"


class doubleRB :
    public beachRoom
{
public:
    string size = "double";

    sqlite3* db;
    char* zErrMsg = 0;
    int rc = sqlite3_open("hotel.db", &db);

    void getRooms();
};

