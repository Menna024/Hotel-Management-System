#pragma once
#include "gardenRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class singleRG :
    public gardenRoom
{
       public:
           string size = "single";
           sqlite3* db;
           char* zErrMsg = 0;
           int rc = sqlite3_open("hotel.db", &db);

           void getRooms();
};

