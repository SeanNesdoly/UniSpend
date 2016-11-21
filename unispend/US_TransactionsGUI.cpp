/*
 * Class	: US_TransactionsGUI.cpp
 * Description 	: Implementation of the transactions tab
 * Author	: Nathaniel
 * Date		: 2016-11-21
 * 
 * Team Lovelace
 * CISC 320 Fall 2016
 */

#include <stdlib.h>
#include <iostream>
#include "US_TransactionsGUI.h"

#include <driver.h>
#include <exception.h>


US_TransactionsGUI::US_TransactionsGUI(WContainerWidget *parent){
	//container setup
	setStyleClass("Transactions");
	
	//Add widgets to container
	title = new WLabel("<h1>UniSpend</h>", this);
	addWidget(title);
}

