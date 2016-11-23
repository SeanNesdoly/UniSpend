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

using namespace Wt;

class US_Workspace : public WContainerWidget
{
public:
    US_Workspace(WContainerWidget *parent);
private:
    void btnLogout_Clicked(); // logout of the application; swap to the login stack container
    WNavigationBar *navigationBar; // navigation bar
    WStackedWidget *tabsStack; // show content based on currently selected tab
    WMenu *leftMenu; // left alligned menu that contains each tab container
    WMenu *rightMenu; // right alligned menu that contains the logout button
    WMenuItem *logout; // logout button within the navigation bar menu

};