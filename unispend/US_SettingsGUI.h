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
#include <Wt/WTableView>

#include <string>
#include "US_Workspace.h"
#include "US_User.h"

using namespace Wt;
using namespace std;

class US_SettingsGUI : public WContainerWidget {
public:
    US_SettingsGUI(US_Workspace *parent);
private:
    User* _user;

    // event handlers
    void btnSaveProjectSettings_Click();
    void btnSaveUserSettings_Click();

    // WIDGETS
    WHBoxLayout* hbox;

    // Project Settings
    WGroupBox* boxProjectSettings;
    WLabel* lblProjectName;
    WLineEdit* txtProjectName;
    WLabel* lblStartBalance;
    WLineEdit* txtStartBalance;
    WLabel* lblStartDate;
    WDateEdit* deStartDate;
    WPushButton* btnSaveProjectSettings;
    WLabel* lblMsgProject; // feedback for project settings

    // Recurring Transactions
    WGroupBox* boxRecurringCosts;
    WTableView* tblRecurringCosts;

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
};