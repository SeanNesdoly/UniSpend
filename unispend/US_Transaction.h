//
// Created by Patrick Gibson on 2016-11-13.
//

#ifndef TRANSACTIONS_US_TRANSACTION_H
#define TRANSACTIONS_US_TRANSACTION_H

#include <string>
//#include "boost/date_time/gregorian/gregorian.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include "string.h"

using namespace std;

class US_Transaction{
public:
    US_Transaction(string username, string name, string type, double value, string date, string recurring, string project);
    string getProject();
    string getName();
    string getUsername();
    string getType();
    double getValue();
    string getDate();
    string getIsRecurring();
    string getId();
//    boost::gregorian::date getDate();
    void setName(const string name);
    void setType(const string type);
    void setValue(const double value);
    void setProjectName(const string projectName);
    void setRecurring(const string recurring);
    void setID(const string ID);

//    void setDate(const boost::gregorian::date date);


private:
    string project;
    string username;
    string name;
    string type;
    double value;
    string date;
    string recurring;
    string id;
};

bool operator==(const US_Transaction& left, const US_Transaction& right);


#endif //TRANSACTIONS_US_TRANSACTION_H
