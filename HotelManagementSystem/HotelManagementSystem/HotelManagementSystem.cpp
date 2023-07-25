using namespace std;

#include <iostream>
#include <string>
#include "people.h"

#define endEmail ".com"
#define passLength 6
const int maxPeopleCount = 10;
people p[maxPeopleCount];
int currentUser = 0;

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

string searchEmailDup(string em,int &indexFoundUser)
{
    for (int i = 0; i < maxPeopleCount; i++)
    {
        string pEmail=p[i].getEmail();

        if (em == pEmail)
        {
            indexFoundUser = i;
            return "This email already has an account on the system";
        }
    }
    return "";
}

string validateUser(string em, string pass)
{
    int index;
    string emDup=searchEmailDup(em,index);

    if (!emDup.empty())
    {
        string registeredPass = p[index].getPassword();

        if (pass != registeredPass)
        {
            return "You entered a wrong password for this email.";
        }
        else
            return "";
    }
    else
        return "This email is not registered on the system.";
}

void errorWrongNum()
{
    cout << "Wrong number entered. Please ty again." << endl;
}


int main()
{                 
    int userMenuNumber;

    string email, password;
    string emError = "", passError = "";
    bool isLogSucc=false, isSignSucc=false, loggedOut=false;
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

        cin >> userMenuNumber;

        switch (userMenuNumber)
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

                  validateEmail(email, emError);

                  if (emError.empty())
                  {
                      string validation = validateUser(email, password);

                      if (validation.empty())
                      {
                          isLogSucc = true;
                          cout << "\nLog in succeeded." << endl;
                      }
                      else
                      {
                          isLogSucc = false;
                          cout << validation << " Try again." << endl;
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
                  string fName, lName;
                  email = "";
                  password = "";
                  emError = "";
                  passError = "";

                  cout << "Sign up" << endl;
                  cout << "Enter your email" << "    ";
                  cin >> email;

                  string emailDup = searchEmailDup(email, currentUser);

                  validateEmail(email, emError);

                  if (emError.empty())
                  {
                      if (emailDup.empty())
                      {                          
                          cout << "Enter your password" << "\t";
                          cin >> password;

                          validatePassword(password, passError);

                          if (passError.empty())
                          {
                              p[currentUser].setEmail(email);
                              p[currentUser].setPassword(password);

                              cout << "Enter your first name" << "\t";
                              cin >> fName;
                              p[currentUser].setFirstName(fName);

                              cout << "Enter your last name" << "\t";
                              cin >> lName;
                              p[currentUser].setLastName(lName);

                              isSignSucc = true;
                              isLogSucc = true;
                              cout << "\nSign up succeeded." << endl;
                              currentUser++;
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
                      int size,view;
                      string aDate, dDate;
                      
                      cout << "\nFill the required rooms specifications." << endl;
                      cout << "What view should it be on?" << endl;
                      cout << "1:Beach  2:Garden  3:Pool" << endl;
                      cin >> view;

                      cout << "What size should it be?" << endl;
                      cout << "1:Single  2:Double  3:Triple" << endl;
                      cin>>size;

                      cout << "What is your arrival date?" << endl;
                      cout << "Day-Month-Year" << endl;
                      cin >> aDate;
                      
                      cout << "What is your departure date?" << endl;
                      cout << "Day-Month-Year" << endl;
                      cin >> dDate;


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
                  } while ( (wantToLogOut==0) || (wantToLogOut>2) );
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
    }while (true);   


}