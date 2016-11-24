/*
 * Class       : US_ForecastGUI.cpp
 * Description : Implementation of the forecasting container.
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include "US_ForecastGUI.h"

US_ForecastGUI::US_ForecastGUI(WContainerWidget *parent):
        WContainerWidget(parent)
{
    setStyleClass("forecasting");

    gridLayout = new WGridLayout();
    this->setLayout(gridLayout);

    // Forecasting parameter widgets
    // ================================
    forecastParameters = new WGroupBox("Forecasting Parameters");
    gridLayout->addWidget(forecastParameters, 0, 0);

    // current scenario selection
    lblScenario = new WLabel("Current Scenario:");
    scenarioList = new WComboBox();
    lblScenario->setBuddy(scenarioList);
    forecastParameters->addWidget(lblScenario);
    forecastParameters->addWidget(scenarioList);

    // target balance
    lblTargetBalance = new WLabel("Target Balance:");
    txtTargetBalance = new WLineEdit();
    lblTargetBalance->setBuddy(txtTargetBalance);
    forecastParameters->addWidget(lblTargetBalance);
    forecastParameters->addWidget(txtTargetBalance);

    // target date
    lblTargetDate = new WLabel("Target Date:");
    deTargetDate = new WDateEdit();
    deTargetDate->setFormat("yyyy-MM-dd");
    deTargetDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblTargetDate->setBuddy(deTargetDate);
    forecastParameters->addWidget(lblTargetDate);
    forecastParameters->addWidget(deTargetDate);

    // Scenario Transactions
    // ========================
    scenarioTransactions = new WGroupBox("Scenario Transactions");
    gridLayout->addWidget(scenarioTransactions, 0, 1);


    // Setting the grid stretch factors
    gridLayout->setColumnStretch(1,1);

    US_Workspace *workspace = dynamic_cast<US_Workspace *>(parent);
    //addWidget(new WLabel(workspace->_user->getFirstName()));
}