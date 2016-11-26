/*
 * Class       : US_ForecastGUI.h
 * Description : Container for the forecasting tab.
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WGridLayout>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WDateEdit>
#include <Wt/WPushButton>

#include "US_Workspace.h"
#include "US_Project.h"

using namespace Wt;

class US_ForecastGUI : public WContainerWidget {
public:
    US_ForecastGUI(US_Workspace *parent);
private:
    User* _user;
    //US_Project currScenario; // currently selected scenario

    // event handlers
    void listScenarios_Changed(); // keep track of the currently selected scenario
    void btnUpdateBalanceAndDate_Click(); // update the current scenario's target balance & date
    void btnCreateNewScenario_Click(); // create a new scenario

    // WIDGETS
    WGridLayout* gridLayout;

    // Forecasting Parameter widgets
    WGroupBox* boxForecastParams;
    WLabel* lblScenario;
    WComboBox* listScenarios;
    WLabel* lblTargetBalance;
    WLineEdit* txtTargetBalance;
    WLabel* lblTargetDate;
    WDateEdit* deTargetDate;
    WPushButton* btnUpdateBalanceAndDate;
    WLabel* lblMsg1; // feedback label for section 1

    // New Scenario widgets
    WGroupBox* boxCreateScenario;
    WLabel* lblNewScenario;
    WLineEdit* txtNewScenario;
    WLabel* lblNewScenarioCost;
    WLineEdit* txtNewScenarioCost;
    WLabel* lblNewStartDate;
    WDateEdit* deNewStartDate;
    WLabel* lblNewTargetDate;
    WDateEdit* deNewTargetDate;
    WPushButton* btnCreateNewScenario;
    WLabel* lblMsg2; // feedback label for section 2

    // Scenario Transaction widgets
    WGroupBox* boxScenarioContent;

};