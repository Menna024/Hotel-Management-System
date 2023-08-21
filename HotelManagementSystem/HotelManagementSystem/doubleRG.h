#pragma once
#include "gardenRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class doubleRG :
    public gardenRoom
{
public:
    string size = "double";

    void displayAvailableRooms();
};

