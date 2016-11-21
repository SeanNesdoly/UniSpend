/*
 * Class       : US_Login.cpp
 * Description : Implementation of the login page.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <stdlib.h>
#include <iostream>

#include "US_Login.h"

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "string.h"

US_Login::US_Login(WContainerWidget *parent):
    WContainerWidget(parent)
{
    // container setup
    setStyleClass("login");

    // adding in widgets to the container
    title = new WLabel("<h1>UniSpend</h1>", this);
    addWidget(title);

    // username label & field
    lblUser = new WLabel("Username:", this);
    txtUser = new WLineEdit(parent);
    lblUser->setBuddy(txtUser);
    addWidget(lblUser);
    addWidget(txtUser);

    // password label & field
    lblPassword = new WLabel("Password:", this);
    txtPassword = new WLineEdit(parent);
    lblPassword->setBuddy(txtPassword);
    addWidget(lblPassword);
    addWidget(txtPassword);

    // navigation to workspace container
    btnLogin = new WPushButton("Login", this);
    btnLogin->clicked().connect(this, &US_Login::btnLogin_Clicked);
    addWidget(btnLogin);

    // error label
    lblError = new WLabel(this);
    lblError->hide();
    addWidget(lblError);


    // Collapsible panel for registering new users
    // ==============================================
    pnlRegisterUser = new WPanel(this);
    pnlRegisterUser->setTitle("<strong>New User? Register Here!</strong>");
    pnlRegisterUser->setStyleClass("register-user");

    pnlRegisterUser->setCollapsible(true);
    pnlRegisterUser->setCollapsed(true);

    // Container for holding fields required for user registration
    newUserContainer = new WContainerWidget(this);
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

    // full name of user
    lblFullName = new WLabel("Full Name:", newUserContainer);
    txtFullName = new WLineEdit(newUserContainer);
    lblFullName->setBuddy(txtFullName);
    newUserContainer->addWidget(lblNewPassword);
    newUserContainer->addWidget(txtNewPassword);

    // handles registration of user
    btnRegisterUser = new WPushButton("Register", newUserContainer);
    btnRegisterUser->clicked().connect(this, &US_Login::btnRegisterUser_Clicked);
    newUserContainer->addWidget(btnRegisterUser);
}

void US_Login::btnLogin_Clicked() {
    // TODO: query database for existing user and handle appropriately
    bool authenticated = true;

    // Test new user account creation
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");

    // Try to retrieve results from the users table
    string username = txtUser->displayText().toUTF8();
    string pass = txtPassword->displayText().toUTF8();
    sql::ResultSet *res;
    bool userExists = false;
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "SELECT `username`, `password` FROM `users` WHERE `username` = '" + username + "'";
    //string sqlCommand = "INSERT INTO `users` (`name`, `password`) VALUES ('" + username + "', '" + pass + "')";

    try
    {
        stmt->execute(sqlCommand);
        stmt->executeQuery(sqlCommand);
        userExists = false;


    } catch(sql::SQLException e)
    {
        cout << endl << "User with name '" << username << "' already exists"  << endl;
        cout << "Please enter a new username and try again" << endl;
        userExists = true;
    }

    if (userExists == false)
    {
        cout << "Successfully created user with name " << username << endl;
    }

    delete stmt;
    delete con;


    if (authenticated) { // successfully authenticated
        WStackedWidget *parent = dynamic_cast<WStackedWidget *>(this->parent());
        parent->setCurrentIndex(1);
        this->clear(); // delete the children of this container
    } else {
        lblError->setText("Invalid username or password");
        lblError->show();
    }
}

void US_Login::btnRegisterUser_Clicked() {
    // TODO: insert a new user into the database
}
