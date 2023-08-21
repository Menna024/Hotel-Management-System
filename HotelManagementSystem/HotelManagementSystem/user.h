#pragma once
#include "people.h"
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"

class user :
    public people
{

public:
    int currentUserId;

    sqlite3* db;
    char* zErrMsg = 0;
    int rc = sqlite3_open("hotel.db", &db);

    void getUserId(string email,string password);
};

