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
    US_Transaction(string name, string type, string value, string date, string recurring);
    string getName();
    string getType();
    string getValue();
//    boost::gregorian::date getDate();
    void setName(const string name);
    void setType(const string type);
    void setValue(const string value);
//    void setDate(const boost::gregorian::date date);
    int addTransaction();


private:
    string name;
    string type;
    string value;
    string date;
    string recurring;
};


#endif //TRANSACTIONS_US_TRANSACTION_H
