using namespace std;

#include <iostream>
#include <string>
#include<stack>
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

singleRB singleRBeach;
singleRG singleRGarden;
singleRP singleRPool;

doubleRB doubleRBeach;
doubleRG doubleRGarden;
doubleRP doubleRPool;

tripleRB tripleRBeach;
tripleRG tripleRGarden;
tripleRP tripleRPool;

#define endEmail ".com"
#define passLength 6

int currentUserId;
user currentUser;
int searchedRooms;
int searchedSuites;

struct date {
    int day, month, year;
}arrivateDate,departureDate;

void validateEmailFormat(string em,string& emError)
{
    bool isComFound = em.find(endEmail) != string::npos;
    bool isAtFound = em.find("@") != string::npos;

    if (isComFound && isAtFound)
        emError = "";
    else
    {
        emError= "\n\n\tWarning:\nWrong email format. Email format is namee22@gmail.com. \n";
    }
}

void validatePasswordFormat(string pass, string& passErorr)
{
    if (pass.length() > passLength)
        passErorr = "";
    else
    {
        passErorr= "\n\tWarning:\nWeak password. Passord length should be more than 6 digits.";
    }
}

void errorWrongNum()
{
    cout << "Wrong number entered. Please ty again." << endl;
}

void getDates()
{
    cout << "Specify Arrival Day: ";
    cin >> arrivateDate.day;
    cout << "Specify Arrival Month: ";
    cin >> arrivateDate.month;
    cout << "Specify Arrival Year: ";
    cin >> arrivateDate.year;

    cout << "Specify Departure Day: ";
    cin >> departureDate.day;
    cout << "Specify Departure Month: ";
    cin >> departureDate.month;
    cout << "Specify Departure Year: ";
    cin >> departureDate.year;
}

void reserveRoom(room &r)
{
    int roomId;
    r.displayAvailableRooms();
    cout << "select the room by typing the id associated: ";
    cin >> roomId;
    getDates();
    bool roomReserved = r.reserveRoom(roomId, currentUser.currentUserId, arrivateDate.day, arrivateDate.month, arrivateDate.year, departureDate.day, departureDate.month, departureDate.year);
    if (roomReserved)
        cout << "Room is reserved successfully " << endl;
    else
        cout << "Reservation Failed. " << endl;
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

int main()
{
    dbManagement dbManage;

    int userMainMenuNumber;
 
    string email, password;
    string emError = "", passError = "";
    bool isLogSucc = false, isSignSucc = false, loggedOut = false;
    bool noRegUse = true;

    cout << "Hello user!" << endl;

    do {
        cout << "\nDo you want to : " << endl;
        cout << "1.Login" << endl;
        cout << "2.Signup" << endl;
        cout << "3.Rooms" << endl;
        cout << "4.Restaurants & Lounges" << endl;
        cout << "5.SPA & Gym" << endl;

        if (isLogSucc || isSignSucc)
        {
            cout << "6.My Reservations" << endl;
            cout << "7.Log out" << endl;
        }

        cin >> userMainMenuNumber;

        switch (userMainMenuNumber)
        {
        case 1:  //LOGIN
        {
            if (isLogSucc == false)
            {
                email = "";
                password = "";
                emError = "";
                passError = "";

                cout << "\nLog in" << endl;
                cout << "Enter your email" << "    ";
                cin >> email;
                cout << "Enter your password" << "\t";
                cin >> password;

                validateEmailFormat(email, emError);

                if (emError.empty())
                {
                    bool isFound = dbManage.validateUser(email, password);

                    if (isFound)
                    {
                        isLogSucc = true;
                        currentUser.getUserId(email,password);
                        cout <<"\nLog in succeeded." << endl;
                    }
                    else
                    {
                        isLogSucc = false;
                        cout << "The email and password you entered are not registered. Please try again." << endl;
                    }
                }
                else   //ERROR : Wrong Email Format
                {
                    cout << emError << endl;
                    isLogSucc = false;
                    cout << "Log in Failed. Please try again." << endl;
                }
            }
            else
                cout << "\tUser already logged in" << endl;
            break;
        }

        case 2:  //SIGNUP
        {
            if (isLogSucc == false)
            {
                string fName, sName;
                email = "";
                password = "";
                emError = "";
                passError = "";

                cout << "Sign up" << endl;
                cout << "Enter your email" << "    ";
                cin >> email;

                validateEmailFormat(email, emError);

                if (emError.empty())
                {
                        cout << "Enter your password" << "\t";
                        cin >> password;

                        validatePasswordFormat(password, passError);
                        

                        if (passError.empty())
                        {
                            bool isADuplicateUser = dbManage.detectDuplicateEmail(email, password);

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
                                
                                isSignSucc = true;
                                isLogSucc = true;

                                currentUser.addUser(email, password, fName, sName, age);
           
                                currentUser.getUserId(email, password);
                               
                               cout << "\n Hello " + currentUser.currentUserId + currentUser.getFirstName() << endl;
                            }
                            else
                            {
                                cout << "Duplicate user " << endl;
                            }
                        }
                        else //ERROR : Password is Weak
                        {
                            cout << passError << endl;
                            isSignSucc = false;
                            cout << "\nSign up failed." << endl;
                        }
                    }
                else   //ERROR : Wrong Email Format
                {
                    isSignSucc = false;
                    cout << emError << endl;
                }
            }
            else
                cout << "\tUser already siggned up" << endl;
            break;
        }

        case 3:  //Rooms
        {
             cout << "Rooms" << endl;

             int size, view;
             string aDate,dDate;

             cout << "What size should it be?" << endl;
             cout << "1:Single  2:Double  3:Triple" << endl;
             cin >> size;

             cout << "\nFill the required rooms specifications." << endl;
             cout << "What view should it be on?" << endl;
             cout << "1:Beach  2:Garden  3:Pool" << endl;
             cin >> view;

             getAvailableRooms(size, view);
              
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
            if (isSignSucc || isLogSucc)
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
            if (isSignSucc || isLogSucc)
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
                        isLogSucc = false;
                        isSignSucc = false;
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
}