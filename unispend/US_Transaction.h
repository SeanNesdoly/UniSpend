//
// Created by Patrick Gibson on 2016-11-13.
//

#ifndef TRANSACTIONS_US_TRANSACTION_H
#define TRANSACTIONS_US_TRANSACTION_H

#include "mysql_connection.h"
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include "mysql_driver.h"
#include "string.h"
#include <vector>

using namespace std;


class US_Transaction{
public:
    US_Transaction(string user, string name, string type, string value, string date, string project);
    string getUser();
    string getName();
    string getType();
    string getValue();
    string getDate();
    string getProject();
    void setUser(const string user);
    void setName(const string name);
    void setType(const string type);
    void setValue(const string value);
    void setDate(const string date);
    void setRecurring(const string recurring);
    friend int deleteTransaction(US_Transaction trans);
    friend void repeatTransaction(string user, string name, string type, string value, string date, string project, string frequency, string range);

private:
    string User;
    string name;
    string type;
    string value;
    string date;
    string recurring;
    string Project;
    int ID;
};


#endif //TRANSACTIONS_US_TRANSACTION_H
