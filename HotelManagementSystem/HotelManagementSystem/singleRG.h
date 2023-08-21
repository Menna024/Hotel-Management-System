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

           void displayAvailableRooms();
};

