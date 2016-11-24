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

#include "US_Workspace.h"

using namespace Wt;

class US_ForecastGUI : public WContainerWidget {
public:
    US_ForecastGUI(WContainerWidget *parent);
private:
    WGridLayout* gridLayout;

    // Forecasting Parameters
    WGroupBox* forecastParameters;
    WLabel* lblScenario;
    WComboBox* scenarioList;
    WLabel* lblTargetBalance;
    WLineEdit* txtTargetBalance;
    WLabel* lblTargetDate;
    WDateEdit* deTargetDate;

    // Scenario Transactions
    WGroupBox* scenarioTransactions;

};