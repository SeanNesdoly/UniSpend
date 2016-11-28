/*
 * Class       : US_Workspace.h
 * Description : The main workspace container for the application. Contains all tab widgets.
 * Author      : srnesdoly
 * Date        : 2016-11-13
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WText>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WLength>
#include <Wt/WDate>
#include <vector>
#include <string>

#include "US_Login.h"
#include "US_User.h"

using namespace Wt;

class US_Workspace : public WContainerWidget
{
public:
    US_Workspace(WContainerWidget *parent, User *user);
    User *user; // authenticated user persisted throughout the application session
    WMenuItem *currentBalance; // current balance for the user

    WStandardItemModel* modelTransactionData;
private:
    WContainerWidget* root; // root widget of the application

    // event handlers
    void btnLogout_Clicked(); // logout of the application; swap to the login stack container

    // WIDGETS
    WNavigationBar *navigationBar; // navigation bar
    WStackedWidget *tabsStack; // show content based on currently selected tab
    WMenu *leftMenu; // left aligned menu that contains each tab container
    WMenu *rightMenu; // right aligned menu that contains the logout button
    WMenuItem *logout; // logout button within the navigation bar menu
};