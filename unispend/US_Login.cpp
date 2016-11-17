/*
 * Class       : US_Login.cpp
 * Description : Implementation of the login page.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <Wt/WApplication>
#include <Wt/WStackedWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "US_Login.h"
//#include "userClass.h"

US_Login::US_Login(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    setStyleClass("login");

    // adding in widgets to the container
    title = new WLabel("<h1>UniSpend</h1>", parent);
    addWidget(title);

    // user label and field
    lblUser = new WLabel("Username:", parent);
    txtUser = new WLineEdit(parent);
    lblUser->setBuddy(txtUser);
    addWidget(lblUser);
    addWidget(txtUser);

    // password label and field
    lblPassword = new WLabel("Password:", parent);
    txtPassword = new WLineEdit(parent);
    lblPassword->setBuddy(txtPassword);
    addWidget(lblPassword);
    addWidget(txtPassword);

    // navigation to workspace container
    btnLogin = new WPushButton("Login");
    btnLogin->clicked().connect(this, &US_Login::btnLogin_Clicked);
    addWidget(btnLogin);

    // error label
    lblError = new WLabel(parent);
    lblError->hide();
    addWidget(lblError);
}

void US_Login::btnLogin_Clicked() {
    // TODO: query database for existing user and handle appropriately
    bool authenticated = true;

    if (authenticated) { // successfully authenticated
        WStackedWidget *parent = dynamic_cast<WStackedWidget *>(this->parent());
        parent->setCurrentIndex(1);
    } else {
        lblError->setText("Invalid username or password");
        lblError->show();
    }
}