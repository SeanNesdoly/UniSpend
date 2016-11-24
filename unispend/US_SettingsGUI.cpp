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
#include <string>

US_SettingsGUI::US_SettingsGUI(WContainerWidget *parent):
        WContainerWidget(parent)
{
    setStyleClass("settings");
    hbox = new WHBoxLayout();
    this->setLayout(hbox);



    // Project-level Settings
    // =======================
    projectSettings = new WGroupBox("Project Settings");
    hbox->addWidget(projectSettings, 1);

    // project name
    lblProjectName = new WLabel("Project Name:");
    txtProjectName = new WLineEdit();
    lblProjectName->setBuddy(txtProjectName);
    projectSettings->addWidget(lblProjectName);
    projectSettings->addWidget(txtProjectName);

    // main project starting balance
    lblStartBalance = new WLabel("Starting Balance:");
    txtStartBalance = new WLineEdit();
    lblStartBalance->setBuddy(txtStartBalance);
    projectSettings->addWidget(lblStartBalance);
    projectSettings->addWidget(txtStartBalance);

    // project start date label & editor
    lblStartDate = new WLabel("Project Start Date:");
    deStartDate = new WDateEdit();
    deStartDate->setFormat("yyyy-MM-dd");
    deStartDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblStartDate->setBuddy(deStartDate);
    projectSettings->addWidget(lblStartDate);
    projectSettings->addWidget(deStartDate);

    // save project settings
    btnSaveProjectSettings = new WPushButton("Save Project Settings");
    btnSaveProjectSettings->clicked().connect(this, &US_SettingsGUI::btnSaveProjectSettings_Click);
    projectSettings->addWidget(btnSaveProjectSettings);


    // User-level Settings
    // ====================
    userSettings = new WGroupBox("User Settings");
    hbox->addWidget(userSettings);

    // password label & field
    lblPassword = new WLabel("Password:");
    txtPassword = new WLineEdit();

    lblPassword->setBuddy(txtPassword);
    userSettings->addWidget(lblPassword);
    userSettings->addWidget(txtPassword);

    // fist name of user
    lblFirstName = new WLabel("First Name:");
    txtFirstName = new WLineEdit();
    lblFirstName->setBuddy(txtFirstName);
    userSettings->addWidget(lblFirstName);
    userSettings->addWidget(txtFirstName);

    // last name of user
    lblLastName = new WLabel("Last Name:");
    txtLastName = new WLineEdit();
    lblLastName->setBuddy(txtLastName);
    userSettings->addWidget(lblLastName);
    userSettings->addWidget(txtLastName);

    // save user settings
    btnSaveUserSettings = new WPushButton("Save User Settings");
    btnSaveUserSettings->clicked().connect(this, &US_SettingsGUI::btnSaveUserSettings_Click);
    userSettings->addWidget(btnSaveUserSettings);
}

// event listener to save currently set project settings
void US_SettingsGUI::btnSaveProjectSettings_Click() {
    // TODO: insert into database
    string projectName = txtProjectName->text().toUTF8();
    WDate date = deStartDate->date();

}

// event listener to save currently set user settings
void US_SettingsGUI::btnSaveUserSettings_Click() {
    // TODO: insert into database
    string pass = txtPassword->text().toUTF8();
    string fName = txtFirstName->text().toUTF8();
    string lName = txtLastName->text().toUTF8();
}