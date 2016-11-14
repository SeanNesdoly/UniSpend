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

#include "US_Workspace.h"

US_Workspace::US_Workspace(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    //WApplication::instance()->setInternalPath("/workspace");
    setStyleClass("workspace");

    // create the navigation bar
    _navigation = new WNavigationBar();
    _navigation->setTitle("UniSpend");
    addWidget(_navigation);

}
