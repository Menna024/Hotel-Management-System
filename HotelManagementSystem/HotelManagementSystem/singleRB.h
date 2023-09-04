#pragma once
#include "beachRoom.h"
#include <string>
using namespace std;
#include <iostream>

class singleRB :
    public beachRoom
{
public:
    string size = "single";

    void displayAvailableRooms(vector<int>& roomsId);
};