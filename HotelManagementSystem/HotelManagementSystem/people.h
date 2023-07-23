#pragma once
#include <string>
using namespace std;
#include <iostream>

class people
{
 private: 
  string firstName;
  string lastName;
  string email;
  string password;

public:
	void setFirstName(string fname);
	void setLastName(string lname);
	void setEmail(string email);
	void setPassword(string password);
	
	string getFirstName();
	string getLastName();
	string getEmail();
	string getPassword();
};

