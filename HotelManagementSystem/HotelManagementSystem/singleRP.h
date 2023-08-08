#pragma once
#include "poolRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"


class singleRP :
    public poolRoom
{
        public:
            string size = "single";
            sqlite3* db;
            char* zErrMsg = 0;
            int rc = sqlite3_open("hotel.db", &db);

            void getRooms();
};

