/*
 * Class       : US_Login.cpp
 * Description : Login container that serves as the initial entrance to the application.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WStackedWidget>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WPanel>

using namespace std;
using namespace Wt;

class US_Login : public WContainerWidget
{
public:
    US_Login(WContainerWidget *parent);

    void handleInternalPath(const string &internalPath);

private:
    void btnLogin_Clicked(); // authenticate user and show workspace container
    void btnRegisterUser_Clicked(); // register a new user in the database
    WLabel* title;
    WLabel* lblUser;
    WLineEdit* txtUser;
    WLabel* lblPassword;
    WLineEdit* txtPassword;
    WPushButton* btnLogin;
    WLabel* lblError;
    WPanel* pnlRegisterUser;
    WContainerWidget* newUserContainer;
    WLabel* lblNewUser;
    WLineEdit* txtNewUser;
    WLabel* lblNewPassword;
    WLineEdit* txtNewPassword;
    WLabel* lblFullName;
    WLineEdit* txtFullName;
    WPushButton* btnRegisterUser;

};
