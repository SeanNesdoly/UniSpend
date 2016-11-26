//
// Created by Patrick Gibson on 2016-11-13.
//

#include "US_Transaction.h"
US_Transaction::US_Transaction(string username, string name, string type, double value, string date, string recurring, string project) {
    this->project = project;
    this->name = name;
    this->username = username;
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

void US_Transaction::setValue(const double value){
    this->value = value;
}

//void US_Transaction::setDate(const boost::gregorian::date date){
//    this->date = date;
//}

string US_Transaction::getProject(){
    return project;
}
string US_Transaction::getUsername(){
    return username;
}
string US_Transaction::getName(){
    return name;
}

string US_Transaction::getType(){
    return type;
}

double US_Transaction::getValue(){
    return value;
}

string US_Transaction::getDate(){
	return date;
}

string US_Transaction::getIsRecurring(){
	return recurring;
}



//boost::gregorian::date US_Transaction::getDate(){
//    return date;
//}



