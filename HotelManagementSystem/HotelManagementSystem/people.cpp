#include "people.h"
#include <string>
using namespace std;
#include <iostream>

void people::setFirstName(string fname)
{
	firstName=fname;
}

void people::setLastName(string lname)
{
	lastName=lname;
}

void people::setEmail(string em)
{
	email = em;
}

void people::setPassword(string pass)
{
	password = pass;
}

void people::setAge(int agee)
{
	age = agee;
}

string people::getFirstName()
{
	return firstName;
}


int people::getAge()
{
	return age;
}
string people::getLastName()
{
	return lastName;
}

string people::getEmail()
{
	return email;
}

string people::getPassword()
{
	return password;
}



