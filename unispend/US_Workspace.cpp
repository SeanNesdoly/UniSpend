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
#include "US_OverviewGUI.h"
#include "US_ForecastGUI.h"
#include "US_SettingsGUI.h"
#include "US_TransactionsGUI.h"

US_Workspace::US_Workspace(WContainerWidget *parent, User *currUser):
    WContainerWidget(parent)
{
    user = currUser; // persisting user across containers
    if (user != nullptr)
        cout << user->getName() << "workspace";
    else
        cout << "FAIL YA SHAT workspace";

    int numTransactions = 3;
    int numCols = 5; // name | type | value | date | isRecurring
    vector<string> headerRow = {"Name", "Type", "Value ($)", "Date (yyyy-mm-dd)", "Recurring cost?"};
    modelTransactionData = new WStandardItemModel(numTransactions, numCols, this);

    for (int row = 0; row < numTransactions; row++) {
        for (int col = 0; col < numCols; col++) {
            WStandardItem *item = new WStandardItem();
            if (row == 0) {
                item->setText(headerRow[col]);
            } else {
                item->setText("Item " + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col));
            }

            modelTransactionData->setItem(row, col, item);
        }
    }

    // container setup
    setStyleClass("workspace");

    // create the navigation bar
    navigationBar = new WNavigationBar();
    navigationBar->setTitle("UniSpend"); // TODO: add in project name
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

    // logout onclick widget
    logout = new WMenuItem("Logout");
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
