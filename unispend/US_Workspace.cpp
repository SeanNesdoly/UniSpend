/*
 * Class       : US_Workspace.cpp
 * Description : Implementation of the workspace container.
 * Author      : srnesdoly
 * Date        : 2016-11-13
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <Wt/WApplication>
#include <Wt/WMenu>
#include <Wt/WText>

#include "US_Workspace.h"
#include "US_TransactionsGUI.h"

US_Workspace::US_Workspace(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    //WApplication::instance()->setInternalPath("/workspace");
    setStyleClass("workspace");

    // create the navigation bar
    _navigation = new WNavigationBar(parent);
    _navigation->setTitle("UniSpend");
    _navigation->setResponsive(true);
    addWidget(_navigation);

    // create the stacked widget that contains each tab
    WStackedWidget *tabsStack = new WStackedWidget(parent);

    WMenu *leftMenu = new WMenu(tabsStack, parent);
    _navigation->addMenu(leftMenu);

    //TODO: NAT replace WText (the 2nd arg) with your generated code classes
    leftMenu->addItem("Overview", new WText("Overview"));
    leftMenu->addItem("Transactions", new US_TransactionsGUI(tabsStack));
    leftMenu->addItem("Forecasting", new WText("Forecasting"));
    leftMenu->addItem("Settings", new WText("Settings"));
	
	addWidget(tabsStack);
}
