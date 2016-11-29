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
    if(recurring == "0")
        this->date = "'" +date+ "'";
    else
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

void US_Transaction::setProjectName(const string projectName){
    this->project = projectName;
}

void US_Transaction::setRecurring(const string recurring){
    this->recurring = recurring;
}

void US_Transaction::setID(const string ID){
    this->id = ID;
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

string US_Transaction::getId(){
    return id;
}

//boost::gregorian::date US_Transaction::getDate(){
//    return date;
//}



