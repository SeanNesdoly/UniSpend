#include <iostream>
using namespace std;

#include "userClass.h" 
#include "userClass.cpp"
int main() 
{
    User userTest("test10", "tester");
    string username = userTest.getName();
    cout << "Username is " << username << endl;
    string password = userTest.getPassword();
    cout << "Password is " << password << endl;
    cout << "Change password to HelloWorld" << endl;
    userTest.setPassword("HelloWorld");
}
