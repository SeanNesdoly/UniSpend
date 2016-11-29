/*
 * Class	: US_TransactionsGUI.cpp
 * Description 	: Implementation of the transactions tab
 * Author	: Nathaniel
 * Date		: 2016-11-28
 * 
 * Team Lovelace
 * CISC 320 Fall 2016
 */

#include <stdlib.h>
#include <iostream>
#include "US_TransactionsGUI.h"

#include <driver.h>
#include <exception.h>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>

#include <Wt/WApplication>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WStringListModel>
#include <Wt/WTableView>
#include <Wt/WItemDelegate>
#include <Wt/WContainerWidget>
#include <Wt/WComboBox>
#include <Wt/WDateEdit>
#include <Wt/WHBoxLayout>

#include "US_User.h"
#include <time.h>


using namespace Wt;
using namespace Wt::Chart;


//Test data
namespace {
	struct Content {
		std::string Date;
		std::string Transaction;
		std::string Category;
		float Cost;
		float Balance;
	
	
		Content(const std::string& aDate, const std::string& aCategory, const std::string& aTransaction, float aCost,float aBalance):
			Date(aDate),
			Category(aCategory),
			Transaction(aTransaction),
			Cost(aCost),
			Balance(aBalance){}

	};

	Content contents[] {
		Content("Nov 01, 2016", "School", "Campus Bookstore", 6.72, 8024.39),
		Content("Nov 01, 2016", "Food", "Loblaws", 93.43, 8031.11),
		Content("Oct 31, 2016", "Rent", "Interac e-Transfer", 547.50, 8124.54),
		Content("Oct 31, 2016", "Food", "A&W", 4.95, 8672.04)
	};

}


US_TransactionsGUI::US_TransactionsGUI(US_Workspace *parent) : WContainerWidget(parent) {
	// Set the global parent
        workspace = parent;
	//Retrive global user object from parent workspace container
	_user = parent->user;
	
	//Container Setup
	setStyleClass("transaction");
	hbox = new WHBoxLayout();
	this->setLayout(hbox);
	divLeft = new WContainerWidget();
	hbox->addWidget(divLeft);
	divRight = new WContainerWidget();
	hbox->addWidget(divRight,1);	

	//////////////////
	//Left Container//
	//////////////////

	//Group box for widgets related to choosing Date Range
	boxDateRange = new WGroupBox("Select Date Range");
	divLeft->addWidget(boxDateRange);	
	
	//Group box for widgets related to Adding a new Transaction
	boxAddTransaction = new WGroupBox("Add Transaction");
	divLeft->addWidget(boxAddTransaction);
	
	
	//Date Range Box contents//
	
	//Dropdown menu for date range
	listDateRange = new WComboBox;	
	listDateRange->addItem("Last Month");
	listDateRange->addItem("Last 3 Months");
	listDateRange->addItem("Last 6 Months");
	
	//Call function on change of comboBox
	listDateRange->changed().connect(this, &US_TransactionsGUI::listDateRange_Change);

//	boxDateRange->addWidget(lblDateRange);
	boxDateRange->addWidget(listDateRange);
	
	//Contents for Add Transactions GroupBox
	lblAddDate = new WLabel("Date:");
	deAddDate = new WDateEdit();
        deAddDate->setFormat("yyyy-MM-dd");
        deAddDate->setDate(WDate::currentServerDate());
	lblAddDate->setBuddy(deAddDate);
	boxAddTransaction->addWidget(lblAddDate);
	boxAddTransaction->addWidget(deAddDate);

	lblAddType = new WLabel("Type:");
	txtAddType = new WLineEdit();
	lblAddType->setBuddy(txtAddType);
	boxAddTransaction->addWidget(lblAddType);
	boxAddTransaction->addWidget(txtAddType);

	lblAddDescription = new WLabel("Transaction Description:");
	txtAddDescription = new WLineEdit();
	lblAddDescription->setBuddy(txtAddDescription);
	boxAddTransaction->addWidget(lblAddDescription);
	boxAddTransaction->addWidget(txtAddDescription);

	lblAddCost = new WLabel("Cost:");
	txtAddCost = new WLineEdit();
	lblAddCost->setBuddy(txtAddCost);
	boxAddTransaction->addWidget(lblAddCost);
	boxAddTransaction->addWidget(txtAddCost);

	//Call function when button is pressed
	btnAddTransaction = new WPushButton("Add New Transaction");
	btnAddTransaction->clicked().connect(this, &US_TransactionsGUI::btnAddTransaction_Click);
 	boxAddTransaction->addWidget(btnAddTransaction);
	

	//Test Label for exceptions
	boxTest = new WGroupBox();
	divLeft->addWidget(boxTest);
	lblTest = new WLabel("Test");
	boxTest->addWidget(lblTest);

	////////////////////	
	//Right Contaniner//
	////////////////////

	
	//GroupBox for Transactons Table
	boxTransactionsTable = new WGroupBox("Transactions");
	divRight->addWidget(boxTransactionsTable);
	
	//Create table with headings
	table = new WTable(boxTransactionsTable);
	table->setHeaderCount(1);
	table->setWidth(Wt::WLength("100%"));
	table->elementAt(0,0)->addWidget(new WText("Date"));
	table->elementAt(0,1)->addWidget(new WText("Type"));
	table->elementAt(0,2)->addWidget(new WText("Transaction Description"));
	table->elementAt(0,3)->addWidget(new WText("Cost"));
	
        reloadMonthly();
	
        //Format table
	table->addStyleClass("table form-inline");
	table->addStyleClass("table-bordered");
	table->addStyleClass("table-hover");
	table->addStyleClass("table-condensed");
	table->addStyleClass("table-striped");
} 

void US_TransactionsGUI::btnAddTransaction_Click() {
    //Set values from text fields into DB
    string dateStr = deAddDate->text().toUTF8();
    cout << dateStr << endl;
    string typeStr = txtAddType->text().toUTF8();
    cout << typeStr << endl;
    string transactionStr = txtAddDescription->text().toUTF8();
    cout << transactionStr << endl;
    string valueStr = txtAddCost->text().toUTF8();
    cout << valueStr << endl;

    // Check for valid data
    if (dateStr.compare("") == 0 || typeStr.compare("") == 0 || transactionStr.compare("") == 0 || valueStr.compare("") == 0)
    {
        cout << "MUST ENTER VALUES FOR ALL FIELDS" << endl;
    }
    else
    {
        double cost = atof(valueStr.c_str());
        // Create the transaction and add to user
        US_Transaction trans(_user->getName(), transactionStr, typeStr, cost, dateStr, "0", "main");
        _user->addTransaction(trans);
        // Update label balance
        ostringstream curBalanceFormat;
        curBalanceFormat << "Balance on " << WDate::currentDate().toString().toUTF8() << ": " << _user->getMain().getCurrentBalance();
        workspace->currentBalance->setText(curBalanceFormat.str());
    
        // Clear text boxes
        txtAddType->setText("");
        txtAddDescription->setText("");
        txtAddCost->setText("");
        deAddDate->setDate(WDate::currentServerDate());

        // Reload monthly table to show the transaction in the transactions table
        reloadMonthly();
    }

}

void US_TransactionsGUI::listDateRange_Change() {
        // Get transactions for range and update table
        cout << "BEFORE TRANSACTIONS" << endl;
        std::ostringstream dateFormat;
        time_t timeObj = time(NULL);
        struct tm *curTime = localtime(&timeObj);

        if (listDateRange->currentIndex() == 0)
        {
            // In the current month index so get the current month from UNIX
            cout << "IN CURRENT MONTH SECTION" << endl;
            dateFormat << "" << (curTime->tm_year + 1900) << "-" << (curTime->tm_mon + 1) << "-01";
            cout << dateFormat.str() << endl;
        }
        else if (listDateRange->currentIndex() == 1)
        {
            cout << "IN 3 MONTH SECTION" << endl;
            dateFormat << "" << (curTime->tm_year + 1900) << "-" << (curTime->tm_mon - 2) << "-01"; 
        }
        else
        {
            // 6 Months
            cout << "IN 6 MONTH SECTION" << endl;
            dateFormat << "" << (curTime->tm_year + 1900) << "-" << (curTime->tm_mon - 5) << "-01";
        }
 
        // First we want to go and get the transactions for a given date range
        vector<US_Transaction> transactionList = _user->getMain().getAllTransactions(dateFormat.str());
       // Clear transaction table before updating
       table->clear();
       table->elementAt(0,0)->addWidget(new WText("Date"));
       table->elementAt(0,1)->addWidget(new WText("Type"));
       table->elementAt(0,2)->addWidget(new WText("Transaction Description"));
       table->elementAt(0,3)->addWidget(new WText("Cost")); 
       // Check if transactions are empty
       if (transactionList.size() == 0)
       {
           cout << "No transactions for given period" << endl;
           table->elementAt(1, 0)->addWidget(new WText("N/A"));
           table->elementAt(1, 1)->addWidget(new WText("N/A"));
           table->elementAt(1, 2)->addWidget(new WText("N/A"));
           table->elementAt(1, 3)->addWidget(new WText("N/A"));
       }
       else
       {
           cout << transactionList.size() << endl;
           // Populate transactions in table
           int row = 0;
           for (int i = 0; i < transactionList.size(); i++)
           {
               row = i + 1;
               // Populate the table
               cout << transactionList.at(i).getDate() << endl;
               // Get transaction date and format
               string transactionDate = transactionList.at(i).getDate();
               string formatDate = transactionDate.substr(1, transactionDate.size()-2);
               table->elementAt(row, 0)->addWidget(new WText(formatDate));
               table->elementAt(row, 1)->addWidget(new WText(transactionList.at(i).getType()));
               table->elementAt(row, 2)->addWidget(new WText(transactionList.at(i).getName()));
               ostringstream convertToString;
               convertToString << transactionList.at(i).getValue();
               table->elementAt(row, 3)->addWidget(new WText(convertToString.str()));

               // delete image button
               WImage* imgDelete = new WImage("resources/delete.png");
               imgDelete->setAttributeValue("row", boost::lexical_cast<std::string>(row));
               table->setAttributeValue("trans_from_date", dateFormat.str());
               table->elementAt(row, 4)->addWidget(imgDelete);
               imgDelete->clicked().connect(std::bind([=] () {
                   WTableRow* theRow = table->rowAt(boost::lexical_cast<int>(imgDelete->attributeValue("row")));
                   theRow->hide();

                   // retrieve column values (testing - will remove)
                   //string date = dynamic_cast<WText*>(theRow->elementAt(0)->widget(0))->text().toUTF8();
                   //string type = dynamic_cast<WText*>(theRow->elementAt(1)->widget(0))->text().toUTF8();
                   //string name = dynamic_cast<WText*>(theRow->elementAt(2)->widget(0))->text().toUTF8();
                   //double value = boost::lexical_cast<double>(dynamic_cast<WText*>(theRow->elementAt(3)->widget(0))->text().toUTF8());

                   // TODO: delete transaction in database
                   vector<US_Transaction> transactionsInCurrRange = _user->getMain().getAllTransactions(table->attributeValue("trans_from_date").toUTF8());
                   US_Transaction transToDelete = transactionsInCurrRange.at(boost::lexical_cast<int>(imgDelete->attributeValue("row")) - 1);
                   cout << transToDelete.getId() << " " << transToDelete.getName() << endl;
                   _user->getMain().deleteTransaction(transToDelete);
               }));
           }
       }

}

void US_TransactionsGUI::reloadMonthly(){
       // Populate with current month info
       listDateRange->setCurrentIndex(0);
        cout << "BEFORE TRANSACTIONS" << endl;
        // Set current index of list picker to 0 because will always revert to 1 month view
        std::ostringstream dateFormat;
        time_t timeObj = time(NULL);
        struct tm *curTime = localtime(&timeObj);
        // In the current month index so get the current month from UNIX
        cout << "IN CURRENT MONTH SECTION" << endl;
        dateFormat << "" << (curTime->tm_year + 1900) << "-" << (curTime->tm_mon + 1) << "-01";
        cout << dateFormat.str() << endl;
        // First we want to go and get the transactions for a given date range
        vector<US_Transaction> transactionList = _user->getMain().getAllTransactions(dateFormat.str());
        // Clear transaction table before updating
       table->clear();
       table->elementAt(0,0)->addWidget(new WText("Date"));
       table->elementAt(0,1)->addWidget(new WText("Type"));
       table->elementAt(0,2)->addWidget(new WText("Transaction Description"));
       table->elementAt(0,3)->addWidget(new WText("Cost"));
       // Check if transactions are empty
       if (transactionList.size() == 0)
       {
           cout << "No transactions for given period" << endl;
           table->elementAt(1, 0)->addWidget(new WText("N/A"));
           table->elementAt(1, 1)->addWidget(new WText("N/A"));
           table->elementAt(1, 2)->addWidget(new WText("N/A"));
           table->elementAt(1, 3)->addWidget(new WText("N/A"));
       }
        else
       {
           cout << transactionList.size() << endl;
           // Populate transactions in table
           int row = 0;
           for (int i = 0; i < transactionList.size(); i++)
           {
               row = i + 1;
               // Populate the table
               cout << transactionList.at(i).getDate() << endl;
               // Get transaction date and format
               string transactionDate = transactionList.at(i).getDate();
               string formatDate = transactionDate.substr(1, transactionDate.size()-2);
               table->elementAt(row, 0)->addWidget(new WText(formatDate));
               table->elementAt(row, 1)->addWidget(new WText(transactionList.at(i).getType()));
               table->elementAt(row, 2)->addWidget(new WText(transactionList.at(i).getName()));
               ostringstream convertToString;
               convertToString << transactionList.at(i).getValue();
               table->elementAt(row, 3)->addWidget(new WText(convertToString.str()));

               // delete image button
               WImage* imgDelete = new WImage("resources/delete.png");
               imgDelete->setAttributeValue("row", boost::lexical_cast<std::string>(row));
               table->setAttributeValue("trans_from_date", dateFormat.str());
               table->elementAt(row, 4)->addWidget(imgDelete);
               imgDelete->clicked().connect(std::bind([=] () {
                   WTableRow* theRow = table->rowAt(boost::lexical_cast<int>(imgDelete->attributeValue("row")));
                   theRow->hide();

                   // retrieve column values (testing - will remove)
                   //string date = dynamic_cast<WText*>(theRow->elementAt(0)->widget(0))->text().toUTF8();
                   //string type = dynamic_cast<WText*>(theRow->elementAt(1)->widget(0))->text().toUTF8();
                   //string name = dynamic_cast<WText*>(theRow->elementAt(2)->widget(0))->text().toUTF8();
                   //double value = boost::lexical_cast<double>(dynamic_cast<WText*>(theRow->elementAt(3)->widget(0))->text().toUTF8());

                   // TODO: delete transaction in database
                   vector<US_Transaction> transactionsInCurrRange = _user->getMain().getAllTransactions(table->attributeValue("trans_from_date").toUTF8());
                   US_Transaction transToDelete = transactionsInCurrRange.at(boost::lexical_cast<int>(imgDelete->attributeValue("row")) - 1);
                   cout << transToDelete.getId() << " " << transToDelete.getName() << endl;
                   _user->getMain().deleteTransaction(transToDelete);
               }));
           }
       }

}

