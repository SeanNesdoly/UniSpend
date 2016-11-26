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

US_Project::US_Project(){
    
}

// this constructor retrieves info from a project in DB
US_Project::US_Project(string username, string pName){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::ResultSet *res2;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");

    res = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = '"+pName+"'");
    res2 = stmt->executeQuery("SELECT EXTRACT(MONTH FROM NOW())");
    res->next();
    res = stmt->executeQuery("SELECT EXTRACT(MONTH FROM '"+res->getString("lastLogin")+"')");
    res2->next();
    res->next();

    // if last login month != current month then reset monthly allowance and add leftover money to leftovers
    if(res->getString(1) != res2->getString(1) && pName == "main"){// res holds the month of a users last login and res2 holds the current month
    	cout << "test" << endl;
    	res = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = '"+pName+"'");
        res->next();
        double yearBalance = res->getDouble("yearBalance");
    	double currMonthlyAllowance = res->getDouble("monthlyAllowance");
        double currLeftover = res->getDouble("leftover");
        double newLeftover = currLeftover + currMonthlyAllowance;

    	res = stmt->executeQuery("SELECT TIMESTAMPDIFF(MONTH, '"+res->getString("startDate")+"', '2017-04-30')"); // 2017-04-30 is hard coded as last day of school for the purpose of simplicity
    	res->next();
        double monthly = yearBalance/res->getInt(1);

        std::ostringstream monthlyStr;
        std::ostringstream leftoverStr;
        monthlyStr << monthly;
        leftoverStr << newLeftover; //use the string stream just like cout, except the stream prints not to stdout but to a string
        std::string monthlyBalance = monthlyStr.str();
        std::string leftoverBalance = leftoverStr.str();
        cout << leftoverBalance << endl;
     	// convert monthly and newLeftover to string then add to update
        string sqlCommand ="UPDATE projects SET monthlyAllowance = " + monthlyBalance + " WHERE projectName = '"+pName+"' AND username ='"+username+"'";
        stmt->execute(sqlCommand);
        sqlCommand ="UPDATE projects SET leftover = " + leftoverBalance + " WHERE projectName = '"+pName+"' AND username ='"+username+"'";
        stmt->execute(sqlCommand);
        sqlCommand ="UPDATE projects SET lastLogin = NOW() WHERE projectName = '"+pName+"' AND username ='"+username+"'";
	stmt->execute(sqlCommand);
    }else{
    	string sqlCommand = "UPDATE projects SET lastLogin = NOW() WHERE username ='"+username+"'";
        stmt->execute(sqlCommand);
    }
    res = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = '"+pName+"'");
    res2 = stmt->executeQuery("SELECT * FROM  `projects` WHERE `username` = '" +username+ "' AND `projectName` = 'main'");
    res2->next();
    res->next();
    this->username = username;
    this->projectName = res->getString("projectName");
    this->currentBalance = res->getDouble("currentBalance");
    this->yearBalance = res->getDouble("yearBalance");
    this->monthlyAllowance = res->getDouble("monthlyAllowance");
    this->leftover = res2->getDouble("leftover");
    this->scenarioCost = res->getDouble("scenarioCost");
    this->startDate = res->getString("startDate");
    this->targetDate = res->getString("targetDate");
    this->id = res->getInt("ID");
    delete res2;
    delete res;
    delete con;
    delete stmt;

}


// US_Project constructor for the main project
US_Project::US_Project(string username, double currentBalance){
    sql :: mysql :: MySQL_Driver *driver;
    sql :: Connection *con;
    sql :: Statement *stmt;
    sql :: ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT TIMESTAMPDIFF(MONTH, NOW(), '2017-04-30')");
    res->next();
    double monthly = currentBalance/res->getInt(1); // in the future this will be changed to allow a user to set theirown period
    cout << monthly << endl;
    std::ostringstream monthlyStr;
    std::ostringstream balanceStr;
    monthlyStr << monthly;
    balanceStr << currentBalance; //use the string stream just like cout, except the stream prints not to stdout but to a string
    std::string monthlyBalance = monthlyStr.str();
    std::string balance = balanceStr.str();

    string sqlCommand = "INSERT INTO `projects` (`username`, `projectName`, `currentBalance`, `lastLogin`, `startDate`, `targetDate`, `yearBalance`, `monthlyAllowance`, `leftover`) VALUES ('" + username + "', 'main', '" + balance + "', NOW() , NOW() , '2017-04-30', '" + balance + "','"+monthlyBalance+ "', '0')";
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
    this->monthlyAllowance = monthly;
    delete res;
    delete con;
    delete stmt;

}
// constructor for scenario project.
US_Project::US_Project(string username, string projectName, double scenarioCost, string targetDate){
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
    double currLeftover = res->getDouble("leftover");
    std::ostringstream sLeftover;
    std::ostringstream scenCost;
    sLeftover << currLeftover;
    scenCost << scenarioCost;
    std::string sLeftoverStr = sLeftover.str();
    std::string scenCostStr = scenCost.str();

    string sqlCommand = "INSERT INTO `projects` (`username`, `projectName`, `scenarioCost`, `lastLogin`, `startDate`, `targetDate`, `leftover`) VALUES ('" + username + "', '" + projectName +"','"+scenCostStr+"', NOW(), NOW(),'"+targetDate+ "','"+sLeftoverStr+ "')";
    // if user attempts to input an ID that already exists the SQLException
    // error will be caught and the user will be asked to try again

    stmt->execute(sqlCommand);

    this->username = username;
    this->projectName = projectName;
    this->leftover = currLeftover;
    this->startDate = res->getString("lastLogin");
    this->targetDate = targetDate;
    this->scenarioCost = scenarioCost;

    delete res;
    delete con;
    delete stmt;
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

void US_Project::updateBalance(double newBalance){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT TIMESTAMPDIFF(MONTH, '"+startDate+"', '2017-04-30')"); // 2017-04-30 is hard coded as last day of school for the purpose of simplicity
    res->next();
    double oldMonthly = res->getInt(1);
    

    res = stmt->executeQuery("SELECT TIMESTAMPDIFF(MONTH, NOW(), '2017-04-30')"); // 2017-04-30 is hard coded as last day of school for the purpose of simplicity
    res->next();
    double newMonthly = newBalance/res->getInt(1);

    double spentSoFar = oldMonthly - monthlyAllowance;
    newMonthly = newMonthly - spentSoFar;
    std::ostringstream monthly;
    std::ostringstream year;
    monthly << newMonthly;
    year << newBalance;
    
    string sqlCommand ="UPDATE projects SET monthlyAllowance = '" + monthly.str() + "' WHERE projectName = 'main' AND username ='"+username+"'";
    stmt->execute(sqlCommand);
    sqlCommand ="UPDATE projects SET yearBalance = '" + year.str() + "' WHERE projectName = 'main' AND username ='"+username+"'";
    stmt->execute(sqlCommand);
    sqlCommand ="UPDATE projects SET startDate = NOW() WHERE projectName = 'main' AND username ='"+username+"'";
    stmt->execute(sqlCommand);




    this-> monthlyAllowance = newMonthly;
    this-> yearBalance = newBalance;
}


// Given a set a set of transactions this method will return the average amount spent per day from the projects start date till present.
double US_Project::getAverage(vector<US_Transaction> transactionsList){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT DATEDIFF(NOW(), '" +startDate+ "')");
    res->next();
    double sum = this->sumAllTransactions(transactionsList);
    double average = sum/res->getDouble(1);
    return average;

}

// returns the daily rate your spending needs to be bellow in order to have enough money to go do the scenario.
double US_Project::getRequiredRate(){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    //sql::ResultSet *res2;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT DATEDIFF(LAST_DAY(NOW()), NOW())");
    res->next();
    double toSaveDaily = monthlyAllowance/res->getDouble(1);

    delete res;
    delete con;
    delete stmt;

    return toSaveDaily;
}


// method used to add a single transaction. adds to the transaction vector of the current project aswell as the SQL DB.
// when impllementing addTransaction we need to check if their are any existing projects for the user. if there is then we need to add transaction to main then add transaction to the project(s). 
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
    // if project is main updat currentBalance and monthlyAllowance as a result of the new transaction 
    // if it's a scenario (not main) then just add the transaction to the scenario transaction vector.
    if(projectName == "main"){
    	double newBalance = currentBalance - newTransaction.getValue();
    	double newMonthlyAllowance = monthlyAllowance - newTransaction.getValue();
    
   	std::ostringstream nMA; //new monthly Allowance
    	std::ostringstream Nb;
    	nMA << newMonthlyAllowance;
    	Nb << newBalance;
    	std::string nMAStr = nMA.str();
    	std::string Nbstr = Nb.str();

    	sqlCommand ="UPDATE projects SET currentBalance = " + Nbstr + " WHERE projectName = 'main' AND username = '"+username+"'";
    	stmt->execute(sqlCommand);

    	sqlCommand ="UPDATE projects SET monthlyAllowance = " + nMAStr + " WHERE projectName = 'main' AND username = '"+username+"'";
    	stmt->execute(sqlCommand);

    	this->currentBalance = newBalance; // adds the value of the transaction to the current balance
    	this->monthlyAllowance = newMonthlyAllowance;
    }
    this->transactions.push_back(newTransaction); // inserts the transaction at the end of vector
    delete con;
    delete stmt;
}

void US_Project::deleteTransaction(US_Transaction trans){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");

    std::ostringstream val; //new monthly Allowance
    val << trans.getValue();


    if(trans.getProject() == "main"){
    	 monthlyAllowance = monthlyAllowance + trans.getValue();
    	 currentBalance = currentBalance + trans.getValue();

         std::ostringstream newMonthlyAllowance;
         newMonthlyAllowance << monthlyAllowance;
         std::ostringstream newCurrentBalance;
         newCurrentBalance << currentBalance;


         string sqlCommand ="UPDATE projects SET currentBalance = " + newCurrentBalance.str() + " WHERE projectName = 'main' AND username = '"+username+"'";
         stmt->execute(sqlCommand);

         sqlCommand ="UPDATE projects SET monthlyAllowance = " + newMonthlyAllowance.str() + " WHERE projectName = 'main' AND username = '"+username+"'";
         stmt->execute(sqlCommand);

    }
    string sqlCommand = "DELETE from `transactions` WHERE `username` = '" +trans.getUsername()+"' AND `name` = '"+trans.getName()+"' AND `type` = '"+trans.getType()+"' AND `value` = '"+val.str()+"' AND `date` = '"+trans.getDate()+"' AND `project` ='"+trans.getProject()+"'";
    try{
        stmt->execute(sqlCommand);
        cout << trans.getProject() << " " << projectName << endl;
    }catch(sql::SQLException e){
        cout << e.what() <<endl;
    }
}


vector<US_Transaction> US_Project::getAllTransactions(){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `project` = '"+projectName+ "'");
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



vector<US_Transaction> US_Project::getAllTransactions(string date){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `project` = '"+projectName+"' AND `date` >= '"+date+ "' AND `date` < NOW() ");
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

vector<US_Transaction> US_Project::getAllTransactions(string date1, string date2){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `date` > '" +date1+ "' AND `date` < '"+date2+ "' AND `username` = '"+username+ "' AND `project` = '"+projectName+"'");
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

vector<US_Transaction> US_Project::getTypeTransactions(string type){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    vector<US_Transaction> results;
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    res = stmt->executeQuery("SELECT * FROM  `transactions` WHERE `username` = '" +username+ "' AND `type` = '"+type+"' AND `project` = '"+projectName+"'");
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
int US_Project::getId(){
    return id;
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

double US_Project::getMonthlyAllowance(){
    return monthlyAllowance;
}

double US_Project::getYearBalance(){
    return yearBalance;
}

double US_Project::getLeftover(){
    return leftover;
}

double US_Project::getScenarioCost(){
    return scenarioCost;
}

vector<US_Transaction> US_Project::getTransactions(){
    return transactions;
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

void US_Project::setTransactions(vector<US_Transaction> transactions){
    this->transactions = transactions;
}

