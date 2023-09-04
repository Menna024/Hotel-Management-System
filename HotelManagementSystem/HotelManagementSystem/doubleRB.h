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

    void displayAvailableRooms(vector<int>& roomsId);
   
};

