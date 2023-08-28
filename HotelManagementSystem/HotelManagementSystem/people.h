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
  int age;

public:
	void setFirstName(string fname);
	void setLastName(string lname);
	void setEmail(string email);
	void setPassword(string password);
	void setAge(int age);
	
	string getFirstName();
	string getLastName();
	string getEmail();
	string getPassword();
	int getAge();
};

