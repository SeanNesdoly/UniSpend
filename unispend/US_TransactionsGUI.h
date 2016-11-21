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

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WStackedWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WPanel>

using namespace std;
using namespace Wt;

class US_TransactionsGUI : public WContainerWidget
{
public:
	US_TransactionsGUI(WContainerWidget *parent);
	
	void handleInternalPath(const string &internalPath);

private:
	void btnAdd_Clicked();
	void btnEdit_Clicked();
	
	WLabel* title;
	WLabel* lblError;
	WPushButton* btnAdd;
	WPushButton* btnEdit;
	WContainerWidget* newUserContainer;
	
};
