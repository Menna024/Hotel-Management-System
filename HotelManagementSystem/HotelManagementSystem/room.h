#pragma once
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

	//Arrival Date
	int bookedDayFrom;
	int bookedMonthFrom; 
	int bookedYearFrom;

	//Departure Date
	int bookedDayTill;
	int bookedMonthTill;
	int bookedYearTill;

	bool reserveRoom(int id);
	bool setArrivalDate(int bookedDay, int bookedMonth, int bookedYear);
	bool setDepartureDate(int bookedDay, int bookedMonth, int bookedYear);

	bool clearRoom();
};

