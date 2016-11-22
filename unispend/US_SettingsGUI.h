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
#include <Wt/WLabel>
#include <Wt/WLineEdit>

using namespace Wt;

class US_SettingsGUI : public WContainerWidget {
public:
    US_SettingsGUI(WContainerWidget *parent);
private:
    WLabel* lblPassword;
    WLineEdit* txtPassword;
    WLabel* lblFirstName;
    WLineEdit* txtFirstName;
    WLabel* lblLastName;
    WLineEdit* txtLastName;
};