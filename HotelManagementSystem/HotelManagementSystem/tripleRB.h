#pragma once
#include "beachRoom.h"
#include <string>
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class tripleRB :
    public beachRoom
{
public:
    string size = "triple";

    void displayAvailableRooms();
};
