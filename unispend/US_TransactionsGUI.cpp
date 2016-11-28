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
	//table->elementAt(0,4)->addWidget(new WText("Balance"));
	
	//Input data, will need to change to retrieving data from database
	for(unsigned i=0; i<4;i++){
		Content content = contents[i];
		int row = i+1;

		table->elementAt(row,0)->addWidget(new WText(content.Date));
		table->elementAt(row,1)->addWidget(new WText(content.Category));
		table->elementAt(row,2)->addWidget(new WText(content.Transaction));
		table->elementAt(row,3)->addWidget(new WText(WString::fromUTF8("{1}").arg(content.Cost)));

	}
	
	//Format table
	table->addStyleClass("table form-inline");
	table->addStyleClass("table-bordered");
	table->addStyleClass("table-hover");
	table->addStyleClass("table-condensed");
	table->addStyleClass("table-striped");
} 

void US_TransactionsGUI::btnAddTransaction_Click() {
	//Set values from text fields into DB
	
	//setDate(txtAddDate);
	//setType(txtAddType);
	//setName(txtAddDescription);
	//setValue(txtAddValue);

}

void US_TransactionsGUI::listDateRange_Change() {
	//Change date range variable 
	//Reload table
		//Create new cells if more data
		//Delete old cells if less data
	
	lblAddTransaction->setText("Test");

}

void US_TransactionsGUI::LoadTable(){
	//Load table from db values	
}

