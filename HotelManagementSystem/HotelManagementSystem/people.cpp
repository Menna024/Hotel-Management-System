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

string people::getFirstName()
{
	return firstName;
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



