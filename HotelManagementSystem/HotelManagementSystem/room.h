#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite/sqlite3.h"
#include "dbManagement.h"

class room
{
  public:

	int id;
	int floor;
	int building;
	double price;
	bool isFree=true;  

	//Info about user that reserved the room
	int userId;
	dbManagement dbManage;
	
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

	
    virtual void displayAvailableRooms(vector<int> &roomsId) = 0;
	bool reserveRoom(int roomId, int userId, int day, int month, int year, int day2, int month2, int year2);
	bool reserveRoomDate(int roomId, int day, int month, int year, int day2, int month2, int year2);
	int getUserVisits(int userID);
	void incrementUserVisits(int userID);

	void clearRoom(int roomId);
};

