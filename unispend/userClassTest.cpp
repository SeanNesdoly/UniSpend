#include <iostream>
using namespace std;

#include "US_User.h" 
#include "US_User.cpp"
int main() 
{
    string userOption;
    cout << "Create (c) user or login (l)?" << endl;
    cin >> userOption;
    string username;
    string password;
    string lastName;
    string firstName;
    // Testing create user
    if (userOption.compare("c") == 0)
    {
       	cout << "Enter username:" << endl;
    	cin >> username;
    	cout << "Enter first name:" << endl;
    	cin >> firstName;
    	cout << "Enter last name:" << endl;
    	cin >> lastName;
    	cout << "Enter password: " << endl;
    	cin >> password;
    	try
   	{
            User createUserTester(username, password, firstName, lastName);
            username = createUserTester.getName();
            cout << "Username is " << username << endl;
            password = createUserTester.getPassword();
            cout << "Password is " << password << endl;
     	} catch (UserException& e)
     	{
             cout << e.what() << endl;
     	}
    }
    else
    {
    	// Test Login
    	cout << "Enter username: " << endl;
    	cin >> username;
    	cout << "Enter password: " << endl;
    	cin >> password;
    	try
    	{
       	    User userLoginTest(username, password);
            cout << "User values:" << endl;
            cout << "Username: " << userLoginTest.getName() << endl;
            cout << "First Name: " << userLoginTest.getFirstName() << endl;
            cout << "Last Name: " << userLoginTest.getLastName() << endl;
            cout << endl << endl;
            cout << "Change pass(cp), change first name(fn), change last name (ln)?" << endl;
            cin >> userOption;
            if (userOption.compare("cp") == 0)
            {
                string newPass;
                cout << "Enter new password" << endl;
                cin >> newPass;
                userLoginTest.setPassword(newPass);
            }
            else if (userOption.compare("fn") == 0)
            {
                string newFName;
                cout << "Enter new first name" << endl;
                cin >> newFName;
                userLoginTest.setFirstName(newFName);
            }
            else if (userOption.compare("ln") == 0)
            {
                string newLName;
                cout << "Enter new last name" << endl;
                cin >> newLName;
                userLoginTest.setLastName(newLName);
            }
            
    	} catch (UserException& e)
    	{
            cout << e.what() << endl;
    	}
    }
}
