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

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>

#include <Wt/WApplication>
#include <Wt/WStandardItemModel>
#include <Wt/WTableView>
//#include "../treeview-dragdrop.CsvUtil.h"


#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>



using namespace Wt;
using namespace Wt::Chart;


namespace {
	struct Content {
		std::string Expense;
		std::string Category;
		int Cost;
	
	
		Content(const std::string& aExpense, const std::string& aCategory,int aCost):
			Expense(aExpense),
			Category(aCategory),
			Cost(aCost){}

	};

	Content contents[] {
		Content("Mucho", "Food", 20),
		Content("Gas","Transport",15),
		Content("TShirt","Clothing",10)
	};

}

US_TransactionsGUI::US_TransactionsGUI(WContainerWidget *parent){
	
	
	//container setup
	setStyleClass("Transactions");
	
	//Add widgets to container
	title = new WLabel("<h1>UniSpend</h1>", this);
	addWidget(title);
	
	test = new WLabel("Hello World", this);
	addWidget(test);
		

	table = new WTable(this);
	table->setHeaderCount(1);
	table->setWidth(Wt::WLength("100%"));

	table->elementAt(0,0)->addWidget(new WText("Expense"));
	table->elementAt(0,1)->addWidget(new WText("Category"));
	table->elementAt(0,2)->addWidget(new WText("$"));
	
	WTableView *tableView = new WTableView(this);
	//tableView->setModel(csvToModel(Wt::WApplication::appRoot() + "table.csv", tableView));
	//tableView->setModel();
	/*tableView->setColumnResizeEnabled(false);
	tableView->setColumnAlignment(0, AlignCenter);
	tableView->setHeaderAlignment(0, AlignCenter);
	tableView->setAlternatingRowColors(true);
	tableView->setRowHeight(28);
	tableView->setHeaderHeight(28);
	tableView->setSelectionMode(SingleSelection);
	tableView->setEditTriggers(WAbstractItemView::NoEditTrigger);

	tableView->elementAt(0,0)->addWidget(new WText("Expense"));
	tableView->elementAt(0,1)->addWidget(new WText("Category"));
	tableView->elementAt(0,2)->addWidget(new WText("$"));
	*/


	for(unsigned i=0; i<3;i++){
		Content content = contents[i];
		int row = i+1;

		table->elementAt(row,0)->addWidget(new WText(content.Expense));
		table->elementAt(row,1)->addWidget(new WText(content.Category));
		table->elementAt(row,2)->addWidget(new WText(WString::fromUTF8("{1}").arg(content.Cost)));
	

		//tableView->elementAt(row,1)->addWidget(new WText(content.Category));
		//tableView->elementAt(row,2)->addWidget(new WLineEdit(WString::fromUTF8("{1}").arg(content.Cost)));
	


	}
	


}

