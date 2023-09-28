#pragma once
#include "people.h"
using namespace std;
#include <iostream>
#include "sqlite/sqlite3.h"
#include "dbManagement.h"

class user :public people{

public:
    int currentUserId;
    
    void addUser(string email, string password, string fName, string sName, int age);
    void getUserId(string email,string password);
};

