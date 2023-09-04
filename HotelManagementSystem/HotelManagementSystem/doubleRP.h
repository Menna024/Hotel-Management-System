#pragma once
#include "poolRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class doubleRP :
    public poolRoom
{
public:
    string size = "double";

    void displayAvailableRooms(vector<int>& roomsId);
};

