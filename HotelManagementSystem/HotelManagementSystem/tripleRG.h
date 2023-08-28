#pragma once
#include "gardenRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class tripleRG :
    public gardenRoom
{
public:
    string size = "triple";

     void displayAvailableRooms();
};

