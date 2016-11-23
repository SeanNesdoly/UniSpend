/*
 * Class       : US_SettingsGUI.cpp
 * Description : Implementation of the settings container
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include "US_SettingsGUI.h"

US_SettingsGUI::US_SettingsGUI(WContainerWidget *parent):
        WContainerWidget(parent)
{
    setStyleClass("settings");

    // password label & field
    lblPassword = new WLabel("Password:");
    txtPassword = new WLineEdit();
    lblPassword->setBuddy(txtPassword);
    addWidget(lblPassword);
    addWidget(txtPassword);

    // fist name of user
    lblFirstName = new WLabel("First Name:");
    txtFirstName = new WLineEdit();
    lblFirstName->setBuddy(txtFirstName);
    addWidget(lblFirstName);
    addWidget(txtFirstName);

    // last name of user
    lblLastName = new WLabel("Last Name:");
    txtLastName = new WLineEdit();
    lblLastName->setBuddy(txtLastName);
    addWidget(lblLastName);
    addWidget(txtLastName);
}