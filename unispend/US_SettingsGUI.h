/*
 * Class       : US_SettingsGUI.h
 * Description : Container for the settings tab.
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WGroupBox>
#include <Wt/WDateEdit>
#include <Wt/WDate>
#include <Wt/WPushButton>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WVBoxLayout>
#include <Wt/WComboBox>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WImage>
#include <Wt/WTableRow>

#include <string>
#include "US_Workspace.h"
#include "US_User.h"

using namespace Wt;
using namespace std;

class US_SettingsGUI : public WContainerWidget {
public:
    US_SettingsGUI(US_Workspace *parent);
    void populateTable();
private:
    User* _user;
    US_Workspace *workspace;

    // event handlers
    void btnSaveProjectSettings_Click();
    void btnSaveUserSettings_Click();
    void btnAddTransaction_Click();

    // WIDGETS
    WHBoxLayout* hbox_root;

    WContainerWidget* divSettings; // div for project & user settings

    // Project Settings
    WGroupBox* boxProjectSettings;
    WLabel* lblStartBalance;
    WLineEdit* txtStartBalance;
    WPushButton* btnSaveProjectSettings;
    WLabel* lblMsgProject; // feedback for project settings

    // User Settings
    WGroupBox* boxUserSettings;
    WLabel* lblPassword;
    WLineEdit* txtPassword;
    WLabel* lblConfirmPassword;
    WLineEdit* txtConfirmPassword;
    WLabel* lblFirstName;
    WLineEdit* txtFirstName;
    WLabel* lblLastName;
    WLineEdit* txtLastName;
    WPushButton* btnSaveUserSettings;
    WLabel* lblMsgUser; // feedback for user settings

    // Recurring Transactions Table
    WGroupBox* boxTable;
    WTable* tblRecurringCosts;

    // Add Recurring Transactions
    WGroupBox* boxAddTransaction;
    WLabel* lblName;
    WLineEdit* txtName;
    WLabel* lblType;
    WLineEdit* txtType;
    WLabel* lblValue;
    WLineEdit* txtValue;
    WLabel* lblDate;
    WDateEdit* deDate;
    WLabel* lblFrequency;
    WComboBox* ddFrequency;
    WLabel* lblNumRepeats;
    WSpinBox* spinNumRepeats;
    WPushButton* btnAddTransaction;
    WLabel* lblMsgTransaction;
};