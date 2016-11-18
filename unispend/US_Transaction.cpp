i/
// Created by Patrick Gibson on 2016-11-13.
//

//sudo g++ -Wall -I/usr/local/include -I/usr/local/include/cppconn -o transTest US_Transaction.cpp -L/usr/local/lib -lmysqlcppconn
#include "US_Transaction.h"
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
US_Transaction::US_Transaction() {}

US_Transaction::US_Transaction(string user, string name, string type, string value, string date, string recurring) {
    this->User = user;
    this->name = name;
    this->type = type;
    this->value = value;
    this->date = date;
    this->recurring = recurring;
}

void US_Transaction::setUser(const string user){
    this->User = user;
}

void US_Transaction::setName(const string name){
    this->name = name;
}

void US_Transaction::setType(const string type){
    this->type = type;
}

void US_Transaction::setValue(const string value){
    this->value = value;
}

void US_Transaction::setDate(const string date) {
    this->date = date;
}

string US_Transaction::getUser(){
    return User;
}

string US_Transaction::getName(){
    return name;
}

string US_Transaction::getType(){
    return type;
}

string US_Transaction::getValue(){
    return value;
}

string US_Transaction::getDate(){
   return date;
}

int US_Transaction::addTransaction() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand =
            "INSERT INTO `transactions` (`User`, `name`, `type`, `value`, `date`, `isRecurring`) VALUES ('" +User+ "','" + name + "','" + type + "','" + value + "','" + date + "','" + recurring + "')";
    stmt->execute(sqlCommand);
    delete con;
    delete stmt;
    return 0;
}

vector<US_Transaction> US_Transaction::getTransaction(const string user){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `User` = '" +user+ "'");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("User"), res->getString("name"), res->getString("type"), res->getString("value")
        ,res->getString("date"), res->getString("isRecurring"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;

}

vector<US_Transaction> US_Transaction::getTransaction(const string user, const string date){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `User` = '" +user+ "' AND `date` >= '"+date+ "' AND `date` < NOW() ");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("User"), res->getString("name"), res->getString("type"), res->getString("value")
                ,res->getString("date"), res->getString("isRecurring"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}

vector<US_Transaction> US_Transaction::getTransactionBetween(const string user, const string date1, const string date2){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `date` > '" +date1+ "' AND `date` < '"+date2+ "' AND `User` = '"+user+"'");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("User"), res->getString("name"), res->getString("type"), res->getString("value")
                ,res->getString("date"), res->getString("isRecurring"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}

int main(){
    cout << "Please enter the following:" << endl;
    cout << "Enter the user: ";
    string user;
    cin >> user;
    cout << "Name: ";
    string name;
    cin >> name;
    string type;
    cout << "Type: ";
    cin >> type;
    string value;
    cout << "Value: ";
    cin >> value;
    string date;
    cout << "Date (as YYYY-MM-DD) : ";
    cin >> date;
    string recurring;
    cout << "Recurring? (1 or 0) : ";
    cin >> recurring;
    US_Transaction trans = US_Transaction(user, name, type, value, date, recurring);
    trans.addTransaction();
    cout << "Name: ";
    string name2;
    cin >> name2;
    string date2;
    cout << "Enter date: ";
    cin >> date2;
    vector<US_Transaction> results = trans.getTransaction(name2, date2);
    for(int i = 0; i < results.size(); i++){
        cout << "\n "+results.at(i).getName() << "\t" +results.at(i).getType() << "\t" +results.at(i).getDate() << endl;
    }




    return 0;
}

