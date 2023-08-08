#include "room.h"
#include <string>
using namespace std;
#include <iostream>


bool room::reserveRoom(int id)
{
  isFree = false;
  userId=id;
  return true;
}

bool room::setArrivalDate(int bookedDay, int bookedMonth, int bookedYear)
{
	bookedDayFrom = bookedDay;
	bookedMonthFrom = bookedMonth;
	bookedYearFrom = bookedYear;

	return true;
}

bool room::setDepartureDate(int bookedDay, int bookedMonth, int bookedYear)
{
	bookedDayTill = bookedDay;
	bookedMonthTill = bookedMonth;
	bookedYearTill = bookedYear;

	return true;
}

bool room::clearRoom()
{
	bookedDayFrom = 0;
	bookedDayTill = 0;
	bookedMonthFrom = 0;
	bookedMonthTill = 0;
	bookedYearFrom = 0;
	bookedYearTill = 0;

	userId = -1;

	return true;
}