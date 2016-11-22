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

US_Workspace::US_Workspace(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    setStyleClass("workspace");

    // create the navigation bar
    navigationBar = new WNavigationBar();
    navigationBar->setTitle("UniSpend");
    navigationBar->setResponsive(true);
    addWidget(navigationBar);

    // create the stacked widget that contains each tab
    tabsStack = new WStackedWidget(parent);
    addWidget(tabsStack);

    // left aligned menu
    leftMenu = new WMenu(tabsStack);
    navigationBar->addMenu(leftMenu);

    // add in the containers for each tab
    leftMenu->addItem("Overview", new US_OverviewGUI(tabsStack));
    leftMenu->addItem("Transactions", new WText("Transactions"));
    leftMenu->addItem("Forecasting", new US_ForecastGUI(tabsStack));
    leftMenu->addItem("Settings", new US_SettingsGUI(tabsStack));

    // right alligned menu
    rightMenu = new WMenu();
    navigationBar->addMenu(rightMenu, AlignRight);

    // logout onclick widget
    logout = new WMenuItem("Logout");
    logout->clicked().connect(this, &US_Workspace::btnLogout_Clicked);
    rightMenu->addItem(logout);

}

void US_Workspace::btnLogout_Clicked() {
    WStackedWidget *parent = dynamic_cast<WStackedWidget *>(this->parent());
    parent->setCurrentIndex(0); // swap to the US_Login container on the main stack
    this->clear(); // delete the children of this container
}
