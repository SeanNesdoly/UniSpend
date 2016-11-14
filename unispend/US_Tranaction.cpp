//
// Created by Patrick Gibson on 2016-11-13.
//

#include "US_Transaction.h"
US_Transaction::US_Transaction(string name, string type, string value, string date, string recurring) {
    this->name = name;
    this->type = type;
    this->value = value;
    this->date = date;
    this->recurring = recurring;
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

//void US_Transaction::setDate(const boost::gregorian::date date){
//    this->date = date;
//}

string US_Transaction::getName(){
    return name;
}

string US_Transaction::getType(){
    return type;
}

string US_Transaction::getValue(){
    return value;
}

//boost::gregorian::date US_Transaction::getDate(){
//    return date;
//}

int US_Transaction::addTransaction() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand =
            "INSERT INTO `transactions` (`name`, `type`, `value`, `date`, `isRecurring`) VALUES ('" + name + "','" + type + "','" + value + "','" + date + "','" + recurring + "')";
    stmt->execute(sqlCommand);
    return 0;
}
int main(){
    cout << "Please enter the following:" << endl;
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
    US_Transaction trans = US_Transaction(name, type, value, date, recurring);
    cout << trans.getName();
    trans.addTransaction();


    return 0;
}

