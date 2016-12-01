/*
 * Class       : US_Workspace.cpp
 * Description : Implementation of the workspace container.
 * Author      : srnesdoly
 * Date        : 2016-11-13
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include "US_Workspace.h"
#include "US_ForecastGUI.h"
#include "US_OverviewGUI.h"
#include "US_SettingsGUI.h"
#include "US_TransactionsGUI.h"

US_Workspace::US_Workspace(WContainerWidget *parent, User *currUser):
    WContainerWidget(parent)
{
    user = currUser; // persisting user across containers

    // CREATING MODELS FOR GRAPHICAL WIDGETS
    /*int numTransactions;
    int numCols;

    // header row
    vector<string> headerRowVals = {"Name", "Type", "Value ($)", "Date (yyyy-mm-dd)", "Frequency"};
    vector<WStandardItem*> headerRow;
    for (int i = 0; i < headerRowVals.size(); i++) {
        WStandardItem *item = new WStandardItem();
        item->setText(headerRowVals.at(i));
        item->setEditable(false);
        headerRow.push_back(item);
    }

//    // FORECASTING TABLE - transaction within range of a scenario
//    numTransactions = 3; // TODO: replace
//    numCols = 5; // name | type | value | date | frequency
//    modelForecastingData = new WStandardItemModel(numTransactions, numCols, this);
//    for (int row = 0; row < numTransactions; row++) {
//        for (int col = 0; col < numCols; col++) {
//            WStandardItem *item = new WStandardItem();
//            item->setText("Item " + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col));
//            modelForecastingData->setItem(row, col, item);
//        }
//    }
//    modelForecastingData->insertRow(0, headerRow);

    // SETTINGS TABLE - recurring transactions
    numTransactions = 3; // TODO: replace
    numCols = 5; // name | type | value | date | frequency
    modelRecurringTransactionData = new WStandardItemModel(numTransactions, numCols, this);
    for (int row = 0; row < numTransactions; row++) {
        for (int col = 0; col < numCols; col++) {
            WStandardItem *item = new WStandardItem();
            item->setText("Item " + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col));
            modelRecurringTransactionData->setItem(row, col, item);
        }
    }
    modelRecurringTransactionData->insertRow(0, headerRow);*/


    // container setup
    setStyleClass("workspace");

    // create the navigation bar
    navigationBar = new WNavigationBar();
    navigationBar->setTitle("UniSpend");
    navigationBar->setResponsive(true);
    addWidget(navigationBar);

    // create the stacked widget that contains each tab
    tabsStack = new WStackedWidget();
    addWidget(tabsStack);

    // left aligned menu
    leftMenu = new WMenu(tabsStack);
    navigationBar->addMenu(leftMenu);

    // add in the containers for each tab
    leftMenu->addItem("Overview", new US_OverviewGUI(this));
    leftMenu->addItem("Transactions", new US_TransactionsGUI(this));
    leftMenu->addItem("Forecasting", new US_ForecastGUI(this));
    leftMenu->addItem("Settings", new US_SettingsGUI(this));

    // right aligned menu
    rightMenu = new WMenu();
    navigationBar->addMenu(rightMenu, AlignRight);

    // current balance for the user
    if (user != nullptr) {
        ostringstream curBalanceFormat;
        curBalanceFormat << "Balance on " << WDate::currentDate().toString().toUTF8() << ": " << user->getMain().getCurrentBalance();
        currentBalance = new WMenuItem(curBalanceFormat.str());
        currentBalance->setCanReceiveFocus(false);
        currentBalance->setSelectable(false);
        currentBalance->setPadding(WLength(30), Wt::Side::Right);
        rightMenu->addItem(currentBalance);
    }

    // logout onclick widget
    logout = new WMenuItem("Logout");
    if (user != nullptr) {
        logout->setText("Logout, " + user->getFirstName() + " " + user->getLastName());
    }
    logout->clicked().connect(this, &US_Workspace::btnLogout_Clicked);
    rightMenu->addItem(logout);

}

void US_Workspace::btnLogout_Clicked() {
    // delete this container and show the login container
    root = WApplication::instance()->root();
    this->clear(); // delete and clean up the children of this container
    root->removeWidget(this);
    US_Login *newLoginContainer = new US_Login(root);
    root->addWidget(newLoginContainer);
}

WMenuItem* US_Workspace::getLogoutLabel()
{
    return logout;
}
