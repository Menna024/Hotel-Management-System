#pragma once
#include "beachRoom.h"
#include <string>
using namespace std;
#include <iostream>

class singleRB :
    public beachRoom
{
public:
    string size = "single";
    sqlite3* db;
    char* zErrMsg = 0;
    int rc = sqlite3_open("hotel.db", &db);

    void getRooms();
};