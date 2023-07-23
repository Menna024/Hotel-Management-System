using namespace std;

#include <iostream>
#include <string>
#include "people.h"

#define endEmail ".com"
#define passLength 6

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
    if (pass.length() >= passLength)
        passErorr = "";
    else
    {
        passErorr= "\n\tWarning:\nWeak password. Passord length should be more than 6 digits.";
    }
}

void login(string em, string pass,string& emError,string& passError)
{
    validateEmail(em, emError);
    validatePassword(pass, passError);
}

int main()
{
    int logOrSign;
    string email, password;
    string emError = "", passError = "";
    bool isLogSucc=false;
    bool isSignSucc=false;

    cout << "Hello user!" << endl;
    cout << "Do you want to : " << endl;
    cout << "1.Login" << endl;
    cout << "or" << endl;
    cout << "2.Signup" << endl;

    do {
      cin >> logOrSign;
      switch (logOrSign)
      { 
         case 1:
         {
             do {
             cout << "\nLog in" << endl;
             cout << "Enter your email" << "    ";
             cin >> email;
             cout << "Enter your password" << "\t";
             cin >> password;          
            
             login(email, password,emError,passError);
             
             if ((emError.empty()) && (passError.empty()))  //if there is no error detected
             {
                 isLogSucc = true;
                 cout<<"\nLog in succeeded";
             }  
             else if (emError.empty())  //if there is an error in the password input
             { 
                 cout << passError << endl;
             } 
             else if (passError.empty())  //if there is an error in the email input
             {
                 cout << emError << endl;
             }
             else  //if there is an error in both, the email and password inputs
             {
                 cout << emError << endl;
                 cout << passError << endl;
             }

             } while (!(emError.empty()) || !(passError.empty()));
             break;
         }
       
        case 2:
        {
            cout << "Sign up"<<endl;
            break;
        }

        default:
        {
            cout << "Wrong number entered. Please ty again." << endl;
            break;
        }
      }
    }while ((logOrSign ==0) || (logOrSign > 2));
}