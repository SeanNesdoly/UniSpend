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

using namespace Wt;

class US_Workspace : public WContainerWidget
{
public:
    US_Workspace(WContainerWidget *parent);
private:
    WNavigationBar *_navigation; // navigation bar
    WStackedWidget *_contentsStack; // show content based on currently selected tab

};