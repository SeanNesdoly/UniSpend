//
// Created by Brent on 11/14/2016.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "US_Transaction.h"
using namespace std;
#ifndef UNISPEND_US_PROJECT_H
#define UNISPEND_US_PROJECT_H


class US_Project {
public:
    US_Project();
    US_Project(string username, string pName);
    US_Project(string username, double currentBalance); //main project
    US_Project(string username, string projectName, double scenarioCost, string endDate); //scenario project
    
    string getUsername();
    string getProjectName();
    int getId();
    double getCurrentBalance();
    string getStartDate();
    double getMonthlyAllowance();
    double getYearBalance();
    double getLeftover();
    double getScenarioCost();

    void setProjectName(string projectName);
    void setCurrentBalance(double currentBalance);
    void setRange(int selectedRange);

    vector<US_Transaction> getAllTransactions();
    vector<US_Transaction> getAllTransactions(string date);
    vector<US_Transaction> getAllTransactions(string date1, string date2);
    vector<US_Transaction> getTypeTransactions(string type);
    void addTransaction(US_Transaction);
    void deleteTransaction(US_Transaction oldTransaction);
    double sumAllTransactions(vector<US_Transaction>);
    double getAverage(vector<US_Transaction>);
protected:
    int id;
    string username;
    string projectName;
    double scenarioCost;
    double currentBalance;
    double yearBalance;
    double monthlyAllowance;
    double leftover;
    string startDate;
    string targetDate;
    vector<US_Transaction> transactions;
};


#endif //UNISPEND_US_PROJECT_H
