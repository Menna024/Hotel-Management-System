using namespace std;

#include <iostream>
#include <string>
#include "people.h"

#define endEmail ".com"
#define passLength 6
const int maxPeopleCount = 10;
people p[maxPeopleCount];


void validateEmail(string em,string& emError)
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

void validatePassword(string pass, string& passErorr)
{
    if (pass.length() > passLength)
        passErorr = "";
    else
    {
        passErorr= "\n\tWarning:\nWeak password. Passord length should be more than 6 digits.";
    }
}

string searchEmailDup(string em)
{
    for (int i = 0; i < maxPeopleCount; i++)
    {
        string pEmail=p[i].getEmail();

        if (em == pEmail)
        {
            return "This email already has an account on the system";
        }
    }
    return "";
}


int main()
{              
    int currentUser = 0;
    
    int userMenuNumber;

    string email, password;
    string emError = "", passError = "";
    bool isLogSucc=false, isSignSucc=false, loggedOut=false;
    bool noRegUse = true;

    cout << "Hello user!" << endl;
   
    do {
        cout << "\nDo you want to : " << endl;
        cout << "1.Login" << endl;
        if (isLogSucc)
            cout << "\tUser already logged in"<<endl;

        cout << "2.Signup" << endl;
        if (isSignSucc)
            cout << "\tUser already siggned up" << endl;

        cout << "3.Rooms & Suites" << endl;
        cout << "4.Restaurants & Lounges" << endl;
        cout << "5.SPA & Gym" << endl;

        if (isLogSucc || isSignSucc)
        {
            cout << "6.My Reservations" << endl;
            cout << "7.Log out" << endl;
        }

        cin >> userMenuNumber;

        switch (userMenuNumber)
        {
          case 1:  //LOGIN
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

              validateEmail(email, emError);

              if (emError.empty())
              {
                  isLogSucc = true;
                  cout << "\nLog in succeeded." << endl;
              }
              else   //ERROR : Wrong Email Format
              {
                  cout << emError << endl;
                  isLogSucc = false;
                  cout << "\nLog in Failed. Please try again." << endl;
              }
              break;
          }

          case 2:  //SIGNUP
          {
              string fName, lName;
              email = "";
              password = "";
              emError = "";
              passError = "";

              cout << "Sign up" << endl;
              cout << "Enter your email" << "    ";
              cin >> email;

              string emailDup = searchEmailDup(email);

              validateEmail(email, emError);

              if (emError.empty())
              {
                  if (emailDup.empty())
                  {
                      p[currentUser].setEmail(email);
                      cout << "Enter your password" << "\t";
                      cin >> password;

                      validatePassword(password, passError);

                      if (passError.empty())
                      {
                          p[currentUser].setPassword(password);
                          isSignSucc = true;

                          cout << "Enter your first name" << "\t";
                          cin >> fName;
                          p[currentUser].setFirstName(fName);

                          cout << "Enter your last name" << "\t";
                          cin >> lName;
                          p[currentUser].setLastName(lName);

                          cout << "\nSign up succeeded." << endl;
                          cout << "\n Hello " + fName << endl;
                      }
                      else //ERROR : Password is Weak
                      {
                          cout << passError << endl;
                          isSignSucc = false;
                          cout << "\nSign up failed." << endl;
                      }
                  }
                  else  //ERROR : Entered Email Already has an account
                  {
                      isSignSucc = false;
                      cout << emailDup << endl;
                  }
              }
              else   //ERROR : Wrong Email Format
              {
                  isSignSucc = false;
                  cout << emError << endl;
              }
              break;
          }

          case 3:  //Rooms & Suites
          {

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
                  cout << "Wrong number entered. Please ty again." << endl;
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
                            cout << "Wrong number entered. Please ty again." << endl;
                            break;
                        }
                      }
                  } while ( (wantToLogOut==0) || (wantToLogOut>2) );
              }
              else
              {
                  cout << "Wrong number entered. Please ty again." << endl;
              }
              break;
          }

          default:
          {
              cout << "Wrong number entered. Please ty again." << endl;
              break;
          }
        }
    }while ((isLogSucc==false) || (isSignSucc==false));   


}