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
    hbox = new WHBoxLayout();
    this->setLayout(hbox);


    // Project-level Settings Section
    // ===============================
    boxProjectSettings = new WGroupBox("Project Settings");
    hbox->addWidget(boxProjectSettings, 0);

    // project name
    lblProjectName = new WLabel("Project Name:");
    txtProjectName = new WLineEdit();
    lblProjectName->setBuddy(txtProjectName);
    boxProjectSettings->addWidget(lblProjectName);
    boxProjectSettings->addWidget(txtProjectName);

    // main project starting balance
    lblStartBalance = new WLabel("Starting Balance:");
    txtStartBalance = new WLineEdit();
    lblStartBalance->setBuddy(txtStartBalance);
    boxProjectSettings->addWidget(lblStartBalance);
    boxProjectSettings->addWidget(txtStartBalance);

    // project start date label & editor
    lblStartDate = new WLabel("Project Start Date:");
    deStartDate = new WDateEdit();
    deStartDate->setFormat("yyyy-MM-dd");
    deStartDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblStartDate->setBuddy(deStartDate);
    boxProjectSettings->addWidget(lblStartDate);
    boxProjectSettings->addWidget(deStartDate);

    // save project settings
    btnSaveProjectSettings = new WPushButton("Save Project Settings");
    btnSaveProjectSettings->clicked().connect(this, &US_SettingsGUI::btnSaveProjectSettings_Click);
    boxProjectSettings->addWidget(btnSaveProjectSettings);

    // user feedback on project settings
    lblMsgProject = new WLabel();
    boxProjectSettings->addWidget(lblMsgProject);



    // Recurring Transactions Section
    // ==================================
    boxRecurringCosts = new WGroupBox("Recurring Transactions");
    hbox->addWidget(boxRecurringCosts, 1);

    // Repeating Transactions Table
    tblRecurringCosts = new WTableView();
    tblRecurringCosts->setAlternatingRowColors(true);
    tblRecurringCosts->setSelectionMode(Wt::SingleSelection);
    boxRecurringCosts->addWidget(tblRecurringCosts);




    // User-level Settings Section
    // =============================
    boxUserSettings = new WGroupBox("User Settings");
    hbox->addWidget(boxUserSettings);

    // password label & field
    lblPassword = new WLabel("New Password:");
    txtPassword = new WLineEdit();
    txtPassword->setEchoMode(WLineEdit::EchoMode::Password);
    lblPassword->setBuddy(txtPassword);
    boxUserSettings->addWidget(lblPassword);
    boxUserSettings->addWidget(txtPassword);

    // confirmation of new password
    lblConfirmPassword = new WLabel("Confirm New Password:");
    txtConfirmPassword = new WLineEdit();
    txtConfirmPassword->setEchoMode(WLineEdit::EchoMode::Password);
    lblConfirmPassword->setBuddy(txtConfirmPassword);
    boxUserSettings->addWidget(lblConfirmPassword);
    boxUserSettings->addWidget(txtConfirmPassword);

    // fist name of user
    lblFirstName = new WLabel("First Name:");
    txtFirstName = new WLineEdit();
    lblFirstName->setBuddy(txtFirstName);
    boxUserSettings->addWidget(lblFirstName);
    boxUserSettings->addWidget(txtFirstName);

    // last name of user
    lblLastName = new WLabel("Last Name:");
    txtLastName = new WLineEdit();
    lblLastName->setBuddy(txtLastName);
    boxUserSettings->addWidget(lblLastName);
    boxUserSettings->addWidget(txtLastName);

    // save user settings
    btnSaveUserSettings = new WPushButton("Save User Settings");
    btnSaveUserSettings->clicked().connect(this, &US_SettingsGUI::btnSaveUserSettings_Click);
    boxUserSettings->addWidget(btnSaveUserSettings);

    // user feedback on user settings
    lblMsgUser = new WLabel();
    boxUserSettings->addWidget(lblMsgUser);
}

// event listener to save currently set project settings
void US_SettingsGUI::btnSaveProjectSettings_Click() {
    // TODO: insert into database
    string projectName = txtProjectName->text().toUTF8();

    // parse starting balance from widget
    double startingBalance;
    try {
        string strStartingBalance = txtStartBalance->text().toUTF8();
        startingBalance = boost::lexical_cast<double>(strStartingBalance);
    } catch(std::exception &e) {
        lblMsgProject->setText("Starting Balance must be a number!");
        lblMsgProject->setStyleClass("error");
        return;
    }

    WDate date = deStartDate->date();

    lblMsgProject->setText("Success!");
    lblMsgProject->setStyleClass("message");

}

// event listener to save currently set user settings
void US_SettingsGUI::btnSaveUserSettings_Click() {
    // TODO: insert into database
    bool failure = false;

    string pass = txtPassword->text().toUTF8();
    string confirmPass = txtConfirmPassword->text().toUTF8();
    if (pass != confirmPass) {
        lblMsgUser->setText("Passwords do not match!");
        lblMsgUser->setStyleClass("error");
        failure = true;
    }

    string fName = txtFirstName->text().toUTF8();
    string lName = txtLastName->text().toUTF8();

    if (!failure) {
        lblMsgUser->setText("Success!");
        lblMsgUser->setStyleClass("message");
    }
}