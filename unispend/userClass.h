#pragma once
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include "string.h"
using namespace std;

class User
{
public: 
    User(const string username, const string& pass);
    string& getName();
    string& getPassword();
    void setPassword(const string& pass);

private:
    string name;
    string password;
    //TODO: ADD US_Project objects ie. mainProject and scenario
};
