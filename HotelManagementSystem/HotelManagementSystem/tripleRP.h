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

     void displayAvailableRooms();
};

