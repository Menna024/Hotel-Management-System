#pragma once

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"


class room
{
  public:
	sqlite3* db;
	char* zErrMsg = 0;
	int rc = sqlite3_open("hotel.db", &db);


	int id;
	int floor;
	int building;
	double price;
	bool isFree=true;  

	//Info about user that reserved the room
	int userId;

	//Arrival Date
	int dayFrom;
	int monthFrom;
	int yearFrom;

	//Departure Date
	int dayTill;
	int monthTill;
	int yearTill;

	bool setArrivalDate(int day,int month,int year);
	bool setDepartureDate(int day, int month, int year);

    virtual void displayAvailableRooms() = 0;
	virtual bool reserveRoom(int roomId, int userId, int day, int month, int year, int day2, int month2, int year2);

	bool clearRoom();
};

