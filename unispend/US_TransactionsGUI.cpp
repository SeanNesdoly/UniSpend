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
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WStringListModel>
#include <Wt/WTableView>
#include <Wt/WItemDelegate>
#include <Wt/WContainerWidget>
#include <Wt/WComboBox>

//#include "../treeview-dragdrop.CsvUtil.h"


#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>



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
	
	
		Content(const std::string& aDate, const std::string& aTransaction, float aCost,float aBalance):
			Date(aDate),
			Transaction(aTransaction),
			Cost(aCost),
			Balance(aBalance){}

	};

	Content contents[] {
		Content("Nov 01, 2016", "Campus Bookstore", 6.72, 8024.39),
		Content("Nov 01, 2016", "Loblaws", 93.43, 8031.11),
		Content("Oct 31, 2016", "Interac e-Transfer", 547.50, 8124.54),
		Content("Oct 31, 2016", "A&W", 4.95, 8672.04)
	};

}

//other crap
class ComboDelegate : public Wt::WItemDelegate {
	public:
		ComboDelegate(WAbstractItemModel* items) : items_(items) {}
	
		void setModelData(const boost::any &editState, WAbstractItemModel* model, const WModelIndex &index) const {
			int stringIdx = (int)asNumber(editState);
			model->setData(index, stringIdx, UserRole);
			model->setData(index, items_->data(stringIdx, 0), DisplayRole);
		}
	
		boost::any editState(WWidget* editor) const {
			WComboBox* combo = dynamic_cast<Wt::WComboBox*>(dynamic_cast<WContainerWidget*>(editor)->widget(0));
			return combo->currentIndex();
		}

		void setEditState(Wt::WWidget* editor, const boost::any &value) const {
			WComboBox* combo = dynamic_cast<WComboBox*>(dynamic_cast<WContainerWidget*>(editor)->widget(0));
			combo->setCurrentIndex((int)asNumber(value));
		}

	protected:
		virtual WWidget* createEditor(const WModelIndex &index,WFlags<ViewItemRenderFlag> flags) const {
			WContainerWidget *const container = new WContainerWidget();
			WComboBox * combo = new WComboBox(container);
			combo->setModel(items_);
			combo->setCurrentIndex((int)asNumber(index.data(UserRole)));
			combo->changed().connect(boost::bind(&ComboDelegate::doCloseEditor, this, container, true));
			combo->enterPressed().connect(boost::bind(&ComboDelegate::doCloseEditor, this, container, true));
			combo->escapePressed().connect(boost::bind(&ComboDelegate::doCloseEditor, this, container, false));
			return container;
		}
	
	private:
		WAbstractItemModel* items_;
		
		void doCloseEditor(WWidget *editor, bool save) const {
			closeEditor().emit(editor,save);
		}
};


US_TransactionsGUI::US_TransactionsGUI(WContainerWidget *parent){
	
	
	//container setup
	setStyleClass("Transactions");
	
	//Add widgets to container
	title = new WLabel("<h1>UniSpend</h1>", this);
	addWidget(title);	

	//test = new WLabel(boost::lexical_cast<string>((setprecision(2) << 3.14)), this);
	//addWidget(test);
	
	//Create table with headings
	table = new WTable(this);
	table->setHeaderCount(1);
	table->setWidth(Wt::WLength("100%"));
	table->elementAt(0,0)->addWidget(new WText("Date"));
	table->elementAt(0,1)->addWidget(new WText("Transaction Description"));
	table->elementAt(0,2)->addWidget(new WText("Cost"));
	table->elementAt(0,3)->addWidget(new WText("Balance"));
	
	//Input data, will need to change to retrieving data from database
	for(unsigned i=0; i<4;i++){
		Content content = contents[i];
		int row = i+1;

		table->elementAt(row,0)->addWidget(new WText(content.Date));
		table->elementAt(row,1)->addWidget(new WText(content.Transaction));
		table->elementAt(row,2)->addWidget(new WText(WString::fromUTF8("{1}").arg(content.Cost)));
		table->elementAt(row,3)->addWidget(new WText(WString::fromUTF8("{1}").arg(content.Balance)));

	}
	
	//Format table
	table->addStyleClass("table form-inline");
	table->addStyleClass("table-bordered");
	table->addStyleClass("table-hover");
	table->addStyleClass("table-condensed");
	table->addStyleClass("table-striped");
	
	
	//Add New Transaction
	//hbox = new WHBoxLayout();
	//this->setLayout(hbox);

	lblAddTransaction = new WLabel("<h3>Add New Transaction</h3>",this);
	
	lblAddDate = new WLabel("Date:",this);
	txtAddDate = new WLineEdit(this);
	//lblAddTransaction->setBuddy(txtAddTransaction);
	addWidget(lblAddDate);
	addWidget(txtAddDate);

	lblAddDescription = new WLabel("Transaction Description:",this);
	txtAddDescription = new WLineEdit(this);
	addWidget(lblAddDescription);
	addWidget(txtAddDescription);

	lblAddCost = new WLabel("Cost:",this);
	txtAddCost = new WLineEdit(this);
	addWidget(lblAddCost);
	addWidget(txtAddCost);

	
	btnAddTransaction = new WPushButton("Add New Transaction");
	//btnAddTransaction->clicked().connect(this, &US_TransactionsGUI::btnAddTransaction_Click);
 	addWidget(btnAddTransaction);
	



	//Extra crap
	WTableView *tableView = new WTableView(this);
	
	std::vector<Wt::WString> Categories;
	Categories.push_back("Food");
	Categories.push_back("Home");
	Categories.push_back("Travel");
	Categories.push_back("Clothing");

	Wt::WStandardItemModel *model = new WStandardItemModel(tableView);
	
	for(unsigned i=0;i<2;i++){
		for(unsigned j=0;j<2;j++){
			WStandardItem *item = new WStandardItem();
			item->setData(0,UserRole);
			item->setData(Categories[0],DisplayRole);
			item->setFlags(ItemIsEditable);
			model->setItem(i,j,item);
		}
	}


	tableView->setModel(model);
	tableView->setEditTriggers(WAbstractItemView::SingleClicked);
	WStringListModel* slModel = new WStringListModel(tableView);
	slModel->setStringList(Categories);
	ComboDelegate* customdelegate = new ComboDelegate(slModel);
	tableView->setItemDelegate(customdelegate);

	tableView->setSortingEnabled(false);	
	tableView->setColumnResizeEnabled(false);
	tableView->setColumnAlignment(0, AlignCenter);
	tableView->setHeaderAlignment(0, AlignCenter);
	tableView->setAlternatingRowColors(true);
	tableView->setRowHeight(40);
	tableView->setHeaderHeight(0);
	
	const int WIDTH = 120;
	for(int i=0;i<tableView->model()->columnCount();i++){
		tableView->setColumnWidth(i,WIDTH);
		tableView->setWidth((WIDTH+7)*tableView->model()->columnCount()+2);
	}



}



