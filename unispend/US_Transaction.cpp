//
// Created by Patrick Gibson on 2016-11-13.
//

//sudo g++ -Wall -I/usr/local/include -I/usr/local/include/cppconn -o transTest US_Transaction.cpp -L/usr/local/lib -lmysqlcppconn
#include "US_Transaction.h"

US_Transaction::US_Transaction(string user, string name, string type, string value, string date, string project) {
    this->User = user;
    this->name = name;
    this->type = type;
    this->value = value;
    this->date = date;
    recurring = '0';
    this->Project = project;
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

void US_Transaction::setRecurring(const string recurring){
    this->recurring = recurring;
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

string US_Transaction::getProject(){
    return Project;
}


int deleteTransaction(US_Transaction trans){
    sql::Connection *con = connect();
    sql::Statement *stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "DELETE from `transactions` WHERE `User` = '" +trans.getUser()+ "' AND `name` = '" +trans.getName()+ "'"
                            "AND `type` = '" +trans.getType()+ "' AND `date` = '" +trans.getDate()+ "'";
    try{
        stmt->execute(sqlCommand);
    }catch(sql::SQLException e){
        cout << e.what() <<endl;
        return -1;
    }
    return 1;

}

void repeatTransaction(string user, string name, string type, string value, string date, string project, string frequency, int range){
    for(int i = 0; i < range; i++) {
        string date2 = "'" + date + "'";
        date2.append(" + INTERVAL ");
        date2.append(to_string(i));
        if (frequency == "daily")
            date2.append(" day");
        else if (frequency == "weekly")
            date2.append(" week");
        else if (frequency == "monthly")
            date2.append(" month");
        else if (frequency == "yearly")
            date2.append(" year");
        US_Transaction trans = US_Transaction(user, name, type, value, date2, project);
        trans.setRecurring("1");
        trans.addTransaction();
    }
}


