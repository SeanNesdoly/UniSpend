/*
 * Class       : US_Login.cpp
 * Description : Implementation of the login page.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>
//#include <Wt/Auth/AuthModel>
//#include <Wt/Auth/AuthWidget>

#include "US_Login.h"

US_Login::US_Login(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    //WApplication::instance()->setInternalPath("/login");
    setStyleClass("login");

    // adding in widgets to the container
    WText *title = new WText("<h1>UniSpend</h1>");
    addWidget(title);

    WPushButton *btnShowWorkspace = new WPushButton("Show Workspace");
    btnShowWorkspace->clicked().connect(this, &US_Login::showWorkspace);
    addWidget(btnShowWorkspace);

    // TODO: wire up the listener for internal path changes
    //WApplication::instance()->internalPathChanged().connect(this, &US_Login::handleInternalPath);

    // TODO: Ryan/Yumou
    // create an authentication widget and add it to the mainStack widget
    //Auth::AuthModel *authModel = new Auth::AuthModel(params);
    //Auth::AuthWidget *authWidget = new Auth::AuthWidget(params);
}

void US_Login::showWorkspace() {
    WStackedWidget *parent = dynamic_cast<WStackedWidget*>(this->parent());
    parent->setCurrentIndex(1);
}

void US_Login::handleInternalPath(const string &internalPath) {
    if (internalPath == "/login") {
        showWorkspace();
    } else {
        WApplication::instance()->setInternalPath("/login", true);
    }
}