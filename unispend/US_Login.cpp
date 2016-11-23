/*
 * Class       : US_Login.cpp
 * Description : Implementation of the login page.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <iostream>

#include "US_Login.h"

US_Login::US_Login(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    setStyleClass("login");

    initializeWidgets();
}

void US_Login::initializeWidgets() {
    // adding in widgets to the container
    title = new WLabel("<h1>UniSpend</h1>");
    addWidget(title);

    // username label & field
    lblUser = new WLabel("Username:");
    txtUser = new WLineEdit();
    lblUser->setBuddy(txtUser);
    addWidget(lblUser);
    addWidget(txtUser);

    // password label & field
    lblPassword = new WLabel("Password:");
    txtPassword = new WLineEdit();
    lblPassword->setBuddy(txtPassword);
    addWidget(lblPassword);
    addWidget(txtPassword);

    // navigation to workspace container
    btnLogin = new WPushButton("Login");
    btnLogin->clicked().connect(this, &US_Login::btnLogin_Clicked);
    addWidget(btnLogin);

    // Collapsible panel for registering new users
    // ==============================================
    pnlRegisterUser = new WPanel();
    pnlRegisterUser->setTitle("<strong>New User? Register Here!</strong>");
    pnlRegisterUser->setStyleClass("register-user");
    pnlRegisterUser->setCollapsible(true);
    pnlRegisterUser->setCollapsed(true);
    addWidget(pnlRegisterUser);

    // Container for holding fields required for user registration
    newUserContainer = new WContainerWidget();
    pnlRegisterUser->setCentralWidget(newUserContainer);

    // username label & field
    lblNewUser = new WLabel("Username:", newUserContainer);
    txtNewUser = new WLineEdit(newUserContainer);
    lblNewUser->setBuddy(txtNewUser);
    newUserContainer->addWidget(lblNewUser);
    newUserContainer->addWidget(txtNewUser);

    // password label & field
    lblNewPassword = new WLabel("Password:", newUserContainer);
    txtNewPassword = new WLineEdit(newUserContainer);
    lblNewPassword->setBuddy(txtNewPassword);
    newUserContainer->addWidget(lblNewPassword);
    newUserContainer->addWidget(txtNewPassword);

    // fist name of user
    lblFirstName = new WLabel("First Name:", newUserContainer);
    txtFirstName = new WLineEdit(newUserContainer);
    lblFirstName->setBuddy(txtFirstName);
    newUserContainer->addWidget(lblFirstName);
    newUserContainer->addWidget(txtFirstName);

    // last name of user
    lblLastName = new WLabel("Last Name:", newUserContainer);
    txtLastName = new WLineEdit(newUserContainer);
    lblLastName->setBuddy(txtLastName);
    newUserContainer->addWidget(lblLastName);
    newUserContainer->addWidget(txtLastName);

    // handles registration of user
    btnRegisterUser = new WPushButton("Register", newUserContainer);
    btnRegisterUser->clicked().connect(this, &US_Login::btnRegisterUser_Clicked);
    newUserContainer->addWidget(btnRegisterUser);

    // error label
    lblErrors = new WLabel();
    lblErrors->setStyleClass("error");
    lblErrors->hide();
    addWidget(lblErrors);
}

void US_Login::btnLogin_Clicked() {
    // user authentication logic
    string username = txtUser->displayText().toUTF8();
    string pass = txtPassword->displayText().toUTF8();

    try {
        _user = new User(username, pass);

        // reaching this statement denotes an authenticated user; create & show the workspace container!
        root = WApplication::instance()->root();
        this->clear(); // delete and clean up the children of this container
        root->removeWidget(this);
        US_Workspace *workspaceContainer = new US_Workspace(root, _user);
        root->addWidget(workspaceContainer);

    } catch (UserException &e) {
        // if an exception is thrown on creation of the user object,
        // the user is not authenticated!
        lblErrors->setText(e.what());
        lblErrors->show();
    }
}

void US_Login::btnRegisterUser_Clicked() {
    // insert a new user into the database and show the workspace container
    string username = txtNewUser->displayText().toUTF8();
    string pass = txtNewPassword->displayText().toUTF8();
    string fName = txtFirstName->displayText().toUTF8();
    string lName = txtLastName->displayText().toUTF8();

    try {
        _user = new User(username, pass, fName, lName);

        // reaching this statement denotes an authenticated user; create & show the workspace container!
        root = WApplication::instance()->root();
        this->clear(); // delete and clean up the children of this container
        root->removeWidget(this);
        US_Workspace *workspaceContainer = new US_Workspace(root, _user);
        root->addWidget(workspaceContainer);

    } catch (UserException &e) {
        // if an exception is thrown on creation of the user object,
        // the user is not authenticated
        lblErrors->setText(e.what());
        lblErrors->show();
    }
}
