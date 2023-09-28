using namespace std;

#include <iostream>
#include <string>
#include <ctime>

#include "sqlite/sqlite3.h"
#include "dbManagement.h"

#include "user.h"

#include "singleRB.h"
#include "doubleRB.h"
#include "tripleRB.h"

#include "singleRG.h"
#include "doubleRG.h"
#include "tripleRG.h"

#include "singleRP.h"
#include "doubleRP.h"
#include "tripleRP.h"

#include <stack>
#include<regex>
#include <windows.h>

#pragma warning(disable : 4996)

singleRB singleRBeach;
singleRG singleRGarden;
singleRP singleRPool;

doubleRB doubleRBeach;
doubleRG doubleRGarden;
doubleRP doubleRPool;

tripleRB tripleRBeach;
tripleRG tripleRGarden;
tripleRP tripleRPool;

int currentUserId=-1;
user currentUser;
stack<int> chosenMenuItems;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct date {
    int day, month, year;
}arrivalDate,departureDate;

void warningWrongEmailFormat()
{
    cout << "Wrong email format\nThe email must: " << endl;
    cout << "\t- contain @ character and . character." << endl;
    cout << "\t- . character should be present after the @ character." << endl;
    cout << "\t- not end with . character." << endl;
}

void warningWrongPasswordFormat()
{
    cout << "Wrong password format\nThe password must: " << endl;
    cout << "\t- have at least one lowercase letter." << endl;
    cout << "\t- contain at least one uppercase letter." << endl;
    cout << "\t- contain at least one number." << endl;
    cout << "\t- contain at least one special character." << endl;
    cout << "\t- not contain any whitespace." << endl;
    cout << "\t- be at least 8 characters long." << endl;

}

bool validateEmailFormat(string em)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    /*
        The \w matches any character in any case any number of times.
        Then the \. | _ matches if a dot or underscore is present 0 or 1 times.
        Then \w again match n characters.
        Then @ matches the @ in the email.
        Then we again check for n charactersand a ‘.’and a word after it, which must be present at least one or more times.
    */

    return regex_match(em, pattern);
}

bool validatePasswordFormat(string pass)
{
    const regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@#$%^&+=])(?=\\S+$).{8,}");
    /*
       (?=.*[a-z]): The password must have at least one lowercase letter.
       
       (?=.*[A-Z]): The password must contain at least one uppercase letter.
       
       (?=.*[0-9]): The password must contain at least one number.
       
       (?=.*[@#$%^&+=]): The password must contain at least one special character.
       
       (?=\\S+$): The password must not contain any whitespace.
       
       .{8,}: The password must be at least 8 characters long.
    */
    return regex_match(pass, pattern);
}

void errorWrongNum()
{
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Wrong number entered. Please ty again." << endl;
}

void validateDay(date date)
{
    while ((date.day <= 0) || (date.day > 31))
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "You entered a wrong day number. Try again." << endl;
        cin >> date.day;
    }
}

void validateMonth(date date)
{
    while ((date.month <= 0) || (date.month > 12))
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "You entered a wrong month number. Try again." << endl;
        cin >> date.month;
    }
}

void validateYear(date date)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    while (date.year < 1900+ltm->tm_year)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "You entered a wrong year. "<<endl;
        cout << "We are currently in year: " << 1900 + ltm->tm_year<<endl;
        cout << "Try again." << endl;
        cin >> date.year;
    }
}

void getDates()
{
    cout << "Specify Arrival Day: ";
    cin >> arrivalDate.day;
    validateDay(arrivalDate);

    cout << "Specify Arrival Month: ";
    cin >> arrivalDate.month;
    validateMonth(arrivalDate);

    cout << "Specify Arrival Year: ";
    cin >> arrivalDate.year;
    validateYear(arrivalDate);

    cout << "Specify Departure Day: ";
    cin >> departureDate.day;
    validateDay(departureDate);

    cout << "Specify Departure Month: ";
    cin >> departureDate.month;
    validateMonth(departureDate);

    cout << "Specify Departure Year: ";
    cin >> departureDate.year;
    validateYear(departureDate);
}

int validateEnteredRoomId(vector<int> availRoomsId)
{
    bool isValidRoomId = false; int roomId;
    do {
        cout << "select the room by typing the id associated: ";
        cin >> roomId;
        vector<int>::iterator it = find(availRoomsId.begin(), availRoomsId.end(), roomId);
        if (it == availRoomsId.end())
        {
            SetConsoleTextAttribute(hConsole, 12);
            isValidRoomId = false;
            cout << "Room ID entered is not valid" << endl;
        }
        else
            isValidRoomId = true;

    } while (!isValidRoomId);

    return roomId;
}

void reserveRoom(room& r)
{
    int roomId;
    vector<int> availRoomsId;

    r.displayAvailableRooms(availRoomsId);

    if (!availRoomsId.empty())
    {
        roomId = validateEnteredRoomId(availRoomsId);
        getDates();
        bool roomReserved = r.reserveRoom(roomId, currentUser.currentUserId, arrivalDate.day, arrivalDate.month, arrivalDate.year, departureDate.day, departureDate.month, departureDate.year);
        if (roomReserved)
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "Room is reserved successfully " << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Reservation Failed. " << endl;
        }
    }
}

void getAvailableRooms(int size, int view)
{
    switch (view)
    { 
      case 1:  //beach
      {
          if (size == 1)
          {
              reserveRoom(singleRBeach);
          }
          else if (size == 2)
          {
              reserveRoom(doubleRBeach);
          }
          else if (size == 3)
          {
              reserveRoom(tripleRBeach);
          }
          break;
      }
     
      case 2:  //garden
      {
          if (size == 1)
          {
             reserveRoom(singleRGarden);
          }
          else if (size == 2)
          {
              reserveRoom(doubleRGarden);
          }
          else if (size == 3)
          {
              reserveRoom(tripleRGarden);
          }
          break;
      }
     
      case 3: //pool
      {
          if (size == 1)
          {
              reserveRoom(singleRPool);
          }
          else if (size == 2)
          {
              reserveRoom(doubleRPool);
          }
          else if (size == 3)
          {
              reserveRoom(tripleRPool);
          }
          break;
      }
    }
}

dbManagement* dbManagement::dbManage = 0;

int main()
{
    dbManagement* db = db->getInstance();
    int userMainMenuNumber, undo=0;

    string email, password;
    bool isUserRegestered = false, loggedOut = false;

    SetConsoleTextAttribute(hConsole,11);
    cout << "Hello user!" << endl;

    do {
        SetConsoleTextAttribute(hConsole,15); //coloring text on console 
        cout << "\nDo you want to : " << endl;
        cout << "1.Login" << endl;
        cout << "2.Signup" << endl;
        cout << "3.Rooms" << endl;
        cout << "4.Restaurants & Lounges" << endl;
        cout << "5.SPA & Gym" << endl;

        if (isUserRegestered)
        {
            cout << "6.My Reservations" << endl;
            cout << "7.Log out" << endl;
        }

        cin >> userMainMenuNumber;

        switch (userMainMenuNumber)
        {
        case 1:  //LOGIN
        {
            if (!isUserRegestered)
            {
                email = "";
                password = "";

                cout << "\nLog in" << endl;
                cout << "Enter your email" << "    ";
                cin >> email;
                cout << "Enter your password" << "\t";
                cin >> password;

                bool val=validateEmailFormat(email);
                
                if (val)
                {
                    bool isFound = db->validateUser(email, password);
                    
                    if (isFound)
                    {
                        isUserRegestered = true;
                        currentUser.getUserId(email, password);
                        cout << "\nLog in succeeded." << endl;
                    }
                    else
                    {
                        isUserRegestered = false;
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "The email and password you entered are not registered. Please try again." << endl;
                    }
                }
                else   //ERROR : Wrong Email Format
                {
                    warningWrongEmailFormat();
                    isUserRegestered = false;
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Log in Failed. Please try again." << endl;
                }
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\tUser already logged in" << endl;
            }
            break;
        }

        case 2:  //SIGNUP
        {
            if (!isUserRegestered)
            {
                cout << "If you want to undo, type 1" << endl;
                cin >> undo;
                if (undo == 1)
                {
                    chosenMenuItems.pop();
                }
                else
                {
                    undo = 0;
                    string fName, sName;
                    email = "";
                    password = "";

                    cout << "Sign up" << endl;
                    cout << "Enter your email" << "    ";
                    cin >> email;

                    bool val = validateEmailFormat(email);
                  
                    if (val)
                    {
                        cout << "Enter your password" << "\t";
                        cin >> password;

                        val=validatePasswordFormat(password);


                        if (val)
                        {
                            bool isADuplicateUser = db->detectDuplicateEmail(email, password);

                            if (!isADuplicateUser)
                            {
                                cout << "Enter your first name" << "\t";
                                cin >> fName;
                                currentUser.setFirstName(fName);

                                cout << "Enter your second name" << "\t";
                                cin >> sName;
                                currentUser.setLastName(sName);

                                cout << "Enter your age" << "\t";
                                int age;
                                cin >> age;
                                currentUser.setAge(age);

                                isUserRegestered = true;

                                currentUser.addUser(email, password, fName, sName, age);

                                currentUser.getUserId(email, password);
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\nSign up succeeded" << endl;
                                cout << "\n Hello " + currentUser.currentUserId + currentUser.getFirstName() << endl;
                            }
                            else
                            {
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "Duplicate user " << endl;
                            }
                        }
                        else //ERROR : Password is Weak
                        {
                            warningWrongPasswordFormat();
                            isUserRegestered = false;
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\nSign up failed." << endl;
                        }
                    }
                    else   //ERROR : Wrong Email Format
                    {
                        warningWrongEmailFormat();

                        isUserRegestered = false;
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "\nSign up failed." << endl;
                    }
                }
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\tUser already siggned up" << endl;
            }

            break;
        }

        case 3:  //Rooms
        {
            if (isUserRegestered)
            {
                SetConsoleTextAttribute(hConsole, 9);
                    cout << "Rooms" << endl;

                    int size, view;
                    string aDate, dDate;

                    cout << "What size should it be?" << endl;
                    cout << "1:Single  2:Double  3:Triple" << endl;
                    cin >> size;

                    cout << "\nFill the required rooms specifications." << endl;
                    cout << "What view should it be on?" << endl;
                    cout << "1:Beach  2:Garden  3:Pool" << endl;
                    cin >> view;

                    getAvailableRooms(size, view);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "Please register first to view and reserve the desired rooms" << endl;
            }

            break;
        }

        case 4:  //Restaurants & Lounges
        {
        
            break;
        }

        case 5:  //SPA & Gym
        {
          
            break;
        }

        case 6:  //My Reservations
        {

            if (isUserRegestered)
            {
                
                
              

            }
            else
            {
                errorWrongNum();
            }

           
            break;
        }
        case 7:  //Log out
        {

            if (isUserRegestered)
            {
                    int wantToLogOut;

                    do
                    {
                        cout << "Are you sure you want to logout?" << endl;
                        cout << "1:Yes  or  2:No" << endl;
                        cin >> wantToLogOut;

                        switch (wantToLogOut)
                        {
                        case 1:
                        {
                            isUserRegestered = false;
                            currentUser.currentUserId = -1;
                            cout << "Log out succeeded. Please visit us soon." << endl;
                            break;
                        }
                        case 2:
                        {
                            cout << "Log out Cancelled." << endl;
                            break;
                        }

                        default:
                        {
                            errorWrongNum();
                            break;
                        }
                        }
                    } while ((wantToLogOut == 0) || (wantToLogOut > 2));
                
            }
            else
            {
                errorWrongNum();
            }

            break;
        }

        default:
        {
            errorWrongNum();
            break;
        }
        }
    } while (true);


    db->closeDB();
}