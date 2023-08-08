using namespace std;

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "dbManagement.h"

#include "people.h"

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

sqlite3* db;
char* zErrMsg = 0;
int rc = sqlite3_open("hotel.db", &db);

int currentUserId;
int searchedRooms;
int searchedSuites;

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

bool validateUser(string em, string pass)
{
    const char* sql = "SELECT * FROM users WHERE email = ? AND password = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Can't prepare select users statement" << endl;
    }
    else
        cout << "Done prepare select users statement" << endl;

    rc = sqlite3_bind_text(stmt, 1, em.c_str(),-1,SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        cout << "Can't bind email" << endl;
    }
    else
        cout << "Done bind email" << endl;

    rc = sqlite3_bind_text(stmt, 2, pass.c_str(),-1,SQLITE_STATIC);
    if(rc!= SQLITE_OK)
    {
        cout << "Can't bind pass" << endl;
    }
    else
        cout << "Done bind pass" << endl;

    bool isUserFound = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int currentUserId = sqlite3_column_int(stmt, 0);
        const char* coll1Val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* coll2Val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        isUserFound = true;
        cout << currentUserId<<", " << coll1Val << ", " << coll2Val << endl;
    }

    return isUserFound;
}

void errorWrongNum()
{
    cout << "Wrong number entered. Please ty again." << endl;
}

void getAvailableRooms(int size, int view)
{
    switch (view)
    {
      case 1:  //beach
      {
          if (size == 1)
          {
              singleRBeach.getRooms();
          }
          else if (size == 2)
          {
              doubleRBeach.getRooms();
          }
          else if (size == 3)
          {
              tripleRBeach.getRooms();
          }
          break;
      }
     
      case 2:  //garden
      {
          if (size == 1)
          {
              singleRGarden.getRooms();
          }
          else if (size == 2)
          {
              doubleRGarden.getRooms();
          }
          else if (size == 3)
          {
              tripleRGarden.getRooms();
          }
          break;
      }
     
      case 3: //pool
      {
          if (size == 1)
          {
              singleRPool.getRooms();
          }
          else if (size == 2)
          {
              doubleRPool.getRooms();
          }
          else if (size == 3)
          {
              tripleRPool.getRooms();
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
        cout << "3.Rooms & Suites" << endl;
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
                    bool isFound = validateUser(email, password);

                    if (isFound)
                    {
                        isLogSucc = true;
                        cout << "\nLog in succeeded." << endl;
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
                            cout << "Enter your first name" << "\t";
                            cin >> fName;
                            
                            cout << "Enter your second name" << "\t";
                            cin >> sName;
                            
                            cout << "Enter your age" << "\t";
                            int age;
                            cin >> age;
                            isSignSucc = true;
                            isLogSucc = true;

                            const char* sql = "INSERT INTO users (email,password,firstName,secondName,age,visits) VALUES (?,?,?,?,?,0);";

                            sqlite3_stmt* stmt;
                            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
                            if (rc != SQLITE_OK)
                            {
                                cout << "Can't prepare statement, " << sqlite3_errmsg(db) <<", " << sqlite3_errcode(db) << endl;
                            }
                            else
                                cout << "DONE prepare statement" << endl;


                            const char* userEm = email.c_str();
                            const char* userPass = password.c_str();
                            const char* userFName = fName.c_str();
                            const char* userSName = sName.c_str();

                            sqlite3_bind_text(stmt, 1, userEm, -1, SQLITE_STATIC);
                            sqlite3_bind_text(stmt, 2, userPass, -1, SQLITE_STATIC);
                            sqlite3_bind_text(stmt, 3, userFName, -1, SQLITE_STATIC);
                            sqlite3_bind_text(stmt, 4, userSName, -1, SQLITE_STATIC);
                            sqlite3_bind_int(stmt, 5, age);
                          

                            rc = sqlite3_step(stmt);
                            if (rc != SQLITE_DONE)
                            {
                                cout << "Can't execute statement " << sqlite3_errmsg(db) << endl;
                            }
                            else
                                cout << "DONE execute statement" << endl;

                           
                            bool x=validateUser(email,password);

                            if(x)
                             cout << "\n Hello " +currentUserId+ fName << endl;
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

        case 3:  //Rooms & Suites
        {
            int choice;
            do {
                cout << "Do you want a room or a suite?" << endl;
                cout << "1.Room." << endl;
                cout << "2.Suite." << endl;
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    int size, view;
                    int aDay, dDay, aMonth, dMonth, aYear, dYear;

                    cout << "What size should it be?" << endl;
                    cout << "1:Single  2:Double  3:Triple" << endl;
                    cin >> size;

                    cout << "\nFill the required rooms specifications." << endl;
                    cout << "What view should it be on?" << endl;
                    cout << "1:Beach  2:Garden  3:Pool" << endl;
                    cin >> view;

                    getAvailableRooms(size, view);

                    cout << "Specify Arrival Date:" << endl;
                    cout << "Day:" << endl;
                    cin >> aDay;
                    cout << "Month:" << endl;
                    cin >> aMonth;
                    cout << "Year:" << endl;
                    cin >> aYear;

                    cout << "Specify Departure Date:" << endl;
                    cout << "Day:" << endl;
                    cin >> dDay;
                    cout << "Month:" << endl;
                    cin >> dMonth;
                    cout << "Year:" << endl;
                    cin >> dYear;


                    break;
                }
                case 2:
                {

                    break;
                }
                default:
                {
                    errorWrongNum();
                    break;
                }
                }
            } while ((choice == 0) || (choice > 2));
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