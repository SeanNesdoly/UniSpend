#pragma once

#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "string.h"

#include "US_Project.h"
#include "US_Transaction.h"

using namespace std;

class User
{
public: 
    // Sign up constructor
    User(const string& username, const string& pass, const string& firstName, const string& lastName);
    // Login constructor
    User(const string& username, const string& pass);

    void updateBalance(double newBalance);
    void addTransaction(US_Transaction newTransaction);
    void deleteTransaction(US_Transaction oldTransaction);
    string& getName();
    string& getPassword();
    string& getFirstName();
    string& getLastName();
    void setPassword(const string& pass);
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setScenarioVector(vector<US_Project> scenList);
    US_Project getMain();
    vector<US_Project> getScenarios();

private:
    string name;
    string password;
    string fName;
    string lName;
    US_Project mainProject;
    vector<US_Project> scenarioProjects;
    //TODO: ADD US_Project objects ie. mainProject and scenario
};

// Exception class
class UserException
{
public:
	// Constructor - sets the provided message to private member
	UserException(const string& outputMsg);
	// Returns the private outputMsg
	string& what();
private:
	// Exception msg
	string outputMsg;
};
