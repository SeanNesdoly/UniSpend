/*
 * Class	: US_TransactionsGUI.h
 * Description 	: Container that containers the Transactions tab
 * Author	: Nathaniel
 * Date		: 2016-11-21
 *
 * Team Lovelace
 * CSIC 320 Fall 2016
*/

#pragma once
#include <stdlib.h>
#include <iostream>

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WStackedWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WPanel>

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>


#include <Wt/WHBoxLayout>
#include <Wt/WGroupBox>

#include "US_Workspace.h"
#include "US_User.h"
#include "US_Project.h"

using namespace std;
using namespace Wt;

class US_TransactionsGUI : public WContainerWidget
{
public:
	US_TransactionsGUI(US_Workspace *parent);
	//US_TransactionsGUI(WContainerWidget *parent);
	
	void btnAddTransaction_Click();
	void listDateRange_Change();
	void reloadMonthly(); 

	void handleInternalPath(const string &internalPath);

private:

	User* _user;
        US_Workspace* workspace;
	void btnAdd_Clicked();
	void btnEdit_Clicked();
		
	WPushButton* btnEdit;
	WContainerWidget* newUserContainer;
	
	WHBoxLayout* hbox;
	WContainerWidget* divLeft;
	WContainerWidget* divRight;	
	
	WGroupBox* boxDateRange;
	WGroupBox* boxAddTransaction;
	WGroupBox* boxTransactionsTable;

	WTable* table;
	WTable* tblTransactions;

	WLabel* lblAddTransaction;
	WLineEdit* txtAddTransaction;
	
	//Add Transaction widgets
	WLabel* lblAddDate;
	WDateEdit* deAddDate;
	WLabel* lblAddType;
	WLineEdit* txtAddType;
	WLabel* lblAddDescription;
	WLineEdit* txtAddDescription;
	WLabel* lblAddCost;
	WLineEdit* txtAddCost;
	WPushButton* btnAddTransaction;
	

	//Date Range Selection
	WLabel* lblDateRange;
	WComboBox* listDateRange;



	WLabel* lblTest;
	WGroupBox* boxTest;

};
