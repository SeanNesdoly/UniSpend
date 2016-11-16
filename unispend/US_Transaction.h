//
// Created by Patrick Gibson on 2016-11-13.
//

#ifndef TRANSACTIONS_US_TRANSACTION_H
#define TRANSACTIONS_US_TRANSACTION_H

#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include "string.h"
#include <vector>

using namespace std;

class US_Transaction{
public:
    US_Transaction();
    US_Transaction(string user, string name, string type, string value, string date, string recurring);
    string getUser();
    string getName();
    string getType();
    string getValue();
    string getDate();
    void setUser(const string user);
    void setName(const string name);
    void setType(const string type);
    void setValue(const string value);
    void setDate(const string date);
    int addTransaction();
    vector<US_Transaction> getTransaction(const string user);
    vector<US_Transaction> getTransaction(const string user, const string date);
    vector<US_Transaction> getTransactionBetween(const string user, const string date1, const string date2);



private:
    string User;
    string name;
    string type;
    string value;
    string date;
    string recurring;
};


#endif //TRANSACTIONS_US_TRANSACTION_H
