//
// Created by Brent on 11/14/2016.
//

#include "US_Project.h"
/*
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include "string.h"
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// this constructor retrieves info from a project in DB
US_Project::US_Project(string username, string pName){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = '"+pName+"'");
    res->next();
    this->username = username;
    this->projectName = res->getString("projectName");
    this->currentBalance = res->getDouble("currentBalance");
    this->scenarioCost = res->getDouble("scenarioCost");
    this->startDate = res->getString("startDate");
    this->targetDate = res->getString("targetDate");
    delete res;
    delete con;
    delete stmt;

}


// US_Project constructor for the main project
US_Project::US_Project(string username, double currentBalance){
    sql :: mysql :: MySQL_Driver *driver;
    sql :: Connection *con;
    sql :: Statement *stmt;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    std::ostringstream balanceStr;
    balanceStr << currentBalance; //use the string stream just like cout, except the stream prints not to stdout but to a string.
    std::string balance = balanceStr.str();
    
    string sqlCommand = "INSERT INTO `projects` (`username`, `projectName`, `currentBalance`) VALUES ('" + username + "', 'main', '" + balance + "')";
    // if user attempts to input an ID that already exists the SQLException
    // error will be caught and the user will be asked to try again
    //try{
    stmt->execute(sqlCommand);


      // }catch(sql::SQLException e) {
        //cout << endl << "The ID is already in use" << endl;
    //}
    this->projectName = "main";
    this->username = username;
    this->currentBalance = currentBalance;

}
// constructor for scenario project.
US_Project::US_Project(string username, string projectName, double scenarioCost, string startDate, string targetDate){
    sql :: mysql :: MySQL_Driver *driver;
    sql :: Connection *con;
    sql :: Statement *stmt;
    sql :: ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = 'main'"); // finds the current balance of a users main project
    res->next();
    double currBalance = res->getDouble("currentBalance");
    std::ostringstream sBalance;
    std::ostringstream scenCost;
    sBalance << currBalance;
    scenCost << scenarioCost;
    std::string sBalanceStr = sBalance.str();
    std::string scenCostStr = scenCost.str();

    string sqlCommand = "INSERT INTO `projects` (`username`, `projectName`, `currentBalance`, `scenarioCost`, `startDate`, `targetDate`) VALUES ('" + username + "', '" + projectName + "', '"+ sBalanceStr +"','"+scenCostStr+"','"+startDate+"','"+targetDate+ "')";
    // if user attempts to input an ID that already exists the SQLException
    // error will be caught and the user will be asked to try again
    try{
        stmt->execute(sqlCommand);
    
    }catch(sql::SQLException e) {
        cout << endl << "The ID is already in use" << endl;
    }
    this->username = username;
    this->projectName = projectName;
    this->currentBalance = currBalance;
    this->startDate = startDate;
    this->targetDate = targetDate;
    this->scenarioCost = scenarioCost;
}



/*
 * US_Project metthods
 */

/*
bool US_Project::isScenario() {
    if(this->bScenario == true){
        return true;
    }else{
        return false;
    }
}
*/

// method used to add a single transaction. adds to the transaction vector of the current project aswell as the SQL DB.
void US_Project::addTransaction(US_Transaction newTransaction){
    sql :: mysql :: MySQL_Driver *driver;
    sql :: Connection *con;
    sql :: Statement *stmt;

    std::ostringstream vstr;
    vstr << newTransaction.getValue(); //use the string stream just like cout, except the stream prints not to stdout but to a string.
    std::string val = vstr.str();

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");

    string sqlCommand = "INSERT INTO `transactions` ( `username`,`name`, `type`, `value`, `date`, `isRecurring`,`project`) VALUES ('"+newTransaction.getUsername()+"','" + newTransaction.getName() + "','" + newTransaction.getType() + "','" +val+"','"+newTransaction.getDate()+"','"+newTransaction.getIsRecurring()+"','"+newTransaction.getProject()+"')";

    //if user attempts to input an ID that already exists the SQLException
    //error will be caught and the user will be asked to try again
    try{
    stmt->execute(sqlCommand);

       }catch(sql::SQLException e){
       cout << endl << "The ID is already in use please input a different id" << endl;
    }
    double newBalance = currentBalance - newTransaction.getValue();

    std::ostringstream Nb;
    Nb << newBalance;
    std::string Nbstr = Nb.str();

    sqlCommand ="UPDATE projects SET currentBalance = " + Nbstr + " WHERE projectName = '"+projectName+"'";
    stmt->execute(sqlCommand);
    this->transactions.insert(this->transactions.end(), newTransaction); // inserts the transaction at the end of vector
    this->currentBalance = newBalance; // adds the value of the transaction to the current balance
}


vector<US_Transaction> US_Project::getAllTransactions(string username, string project){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `project` = '"+project+ "'");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("username"), res->getString("name"), res->getString("type"), res->getDouble("value")
                ,res->getString("date"), res->getString("isRecurring"), res->getString("project"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}



vector<US_Transaction> US_Project::getAllTransactions(string username, string project, string date){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `project` = '"+project+"' AND `date` >= '"+date+ "' AND `date` < NOW() ");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("username"), res->getString("name"), res->getString("type"), res->getDouble("value")
                ,res->getString("date"), res->getString("isRecurring"), res->getString("project"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}

vector<US_Transaction> US_Project::getAllTransactions(string username, string project, string date1, string date2){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `date` > '" +date1+ "' AND `date` < '"+date2+ "' AND `username` = '"+username+ "' AND `project` = '"+project+"'");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("username"), res->getString("name"), res->getString("type"), res->getDouble("value")
                ,res->getString("date"), res->getString("isRecurring"), res->getString("project"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}

vector<US_Transaction> US_Project::getTypeTransactions(string username, string project, string type){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `type` = '"+type+"' AND `project` = '"+project+"'");
    while(res->next()){
        US_Transaction* trans = new US_Transaction(res->getString("username"), res->getString("name"), res->getString("type"), res->getDouble("value")
                ,res->getString("date"), res->getString("isRecurring"), res->getString("project"));
        results.push_back(*trans);
    }
    delete res;
    delete con;
    delete stmt;
    return results;
}






/*
void US_Project::deleteTransaction(US_Transaction oldTransaction){
    for(int i=0; i < this->transactions.size(); i++){
        // if oldTransaction ID equals the current transaction ID erase it from Transactions vector.
        if(this->transactions.at(i).getTransactionId() == oldTransaction.getTransactionId()){
            this->transactions.erase(this->transactions.begin()+i);
            this->currentBalance = this->currentBalance - oldTransaction.getValue(); // subtracts the value of a transaction from current ballance
        }
    }
}
*/
// Sums all transactions of a project up until endDate
double US_Project::sumAllTransactions(vector<US_Transaction> transactionList){
    double sum = 0;
    for(unsigned int i=0; i < transactionList.size(); i++){
        sum = sum + transactionList.at(i).getValue();
    }
    return sum;
}



/*
 * Getters
 */
int US_Project::getProjectId(){
    return projectID;
}

string US_Project::getProjectName(){
    return projectName;
}

string US_Project::getUsername(){
    return username;
}

double US_Project::getCurrentBalance() {
    return currentBalance;
}

string US_Project::getStartDate() {
    return startDate;
}

/*
 * Setters
 */

void US_Project::setProjectName(string projectName){
    this->projectName = projectName;
}

void US_Project::setCurrentBalance(double currentBalance){
    this->currentBalance = currentBalance;
}

