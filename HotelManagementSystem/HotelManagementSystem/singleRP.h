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

            void displayAvailableRooms(vector<int>& roomsId);
};

