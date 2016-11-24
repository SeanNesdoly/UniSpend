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

#include <string>

using namespace Wt;
using namespace std;

class US_SettingsGUI : public WContainerWidget {
public:
    US_SettingsGUI(WContainerWidget *parent);
private:
    void btnSaveProjectSettings_Click();
    void btnSaveUserSettings_Click();

    WHBoxLayout* hbox;

    // Project Settings
    WGroupBox* projectSettings;
    WLabel* lblProjectName;
    WLineEdit* txtProjectName;
    WLabel* lblStartBalance;
    WLineEdit* txtStartBalance;
    WLabel* lblStartDate;
    WDateEdit* deStartDate;
    WPushButton* btnSaveProjectSettings;

    // User Settings
    WGroupBox* userSettings;
    WLabel* lblPassword;
    WLineEdit* txtPassword;
    WLabel* lblFirstName;
    WLineEdit* txtFirstName;
    WLabel* lblLastName;
    WLineEdit* txtLastName;
    WPushButton* btnSaveUserSettings;
};