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

    // Retrieve the user object from the workspace class
    US_Workspace *workspace = dynamic_cast<US_Workspace *>(parent);
    //workspace->_user->getProjects()???? // TODO: get projects
    //addWidget(new WLabel(workspace->_user->getFirstName()));

    // Forecasting tab layout
    gridLayout = new WGridLayout();
    this->setLayout(gridLayout);

    // Forecasting Parameter widgets
    // ================================
    boxForecastParams = new WGroupBox("Forecasting Parameters");
    gridLayout->addWidget(boxForecastParams, 0, 0);

    // current scenario selection
    lblScenario = new WLabel("Current Scenario:");
    listScenarios = new WComboBox();
    listScenarios->changed().connect(this, &US_ForecastGUI::listScenarios_Changed);
    lblScenario->setBuddy(listScenarios);
    boxForecastParams->addWidget(lblScenario);
    boxForecastParams->addWidget(listScenarios);

    // target balance
    lblTargetBalance = new WLabel("Target Balance:");
    txtTargetBalance = new WLineEdit();
    lblTargetBalance->setBuddy(txtTargetBalance);
    boxForecastParams->addWidget(lblTargetBalance);
    boxForecastParams->addWidget(txtTargetBalance);

    // target date
    lblTargetDate = new WLabel("Target Date:");
    deTargetDate = new WDateEdit();
    deTargetDate->setFormat("yyyy-MM-dd");
    deTargetDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblTargetDate->setBuddy(deTargetDate);
    boxForecastParams->addWidget(lblTargetDate);
    boxForecastParams->addWidget(deTargetDate);

    btnUpdateBalanceAndDate = new WPushButton("Update Target Balance & Date");
    btnUpdateBalanceAndDate->clicked().connect(this, &US_ForecastGUI::btnUpdateBalanceAndDate_Click);
    boxForecastParams->addWidget(btnUpdateBalanceAndDate);

    // message label 1
    lblMsg1 = new WLabel();
    boxForecastParams->addWidget(lblMsg1);



    // New Scenario widgets
    // =======================
    boxCreateScenario = new WGroupBox("Create a New Scenario");
    gridLayout->addWidget(boxCreateScenario, 1, 0);

    // new scenario name
    lblNewScenario = new WLabel("New Scenario Name:");
    txtNewScenario = new WLineEdit();
    lblNewScenario->setBuddy(txtNewScenario);
    boxCreateScenario->addWidget(lblNewScenario);
    boxCreateScenario->addWidget(txtNewScenario);

    // new scenario cost
    lblNewScenarioCost = new WLabel("New Scenario Cost:");
    txtNewScenarioCost = new WLineEdit();
    lblNewScenarioCost->setBuddy(txtNewScenarioCost);
    boxCreateScenario->addWidget(lblNewScenarioCost);
    boxCreateScenario->addWidget(txtNewScenarioCost);

    // new scenario start date
    lblNewStartDate = new WLabel("New Scenario Start Date:");
    deNewStartDate = new WDateEdit();
    deNewStartDate->setFormat("yyyy-MM-dd");
    deNewStartDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblNewStartDate->setBuddy(deNewStartDate);
    boxCreateScenario->addWidget(lblNewStartDate);
    boxCreateScenario->addWidget(deNewStartDate);

    // new scenario target date
    lblNewTargetDate = new WLabel("New Scenario Target Date:");
    deNewTargetDate = new WDateEdit();
    deNewTargetDate->setFormat("yyyy-MM-dd");
    deNewTargetDate->setDate(WDate::currentServerDate()); // TODO: from database
    lblNewTargetDate->setBuddy(deNewTargetDate);
    boxCreateScenario->addWidget(lblNewTargetDate);
    boxCreateScenario->addWidget(deNewTargetDate);

    // create new scenario button
    btnCreateNewScenario = new WPushButton("Create New Scenario");
    btnCreateNewScenario->clicked().connect(this, &US_ForecastGUI::btnCreateNewScenario_Click);
    boxCreateScenario->addWidget(btnCreateNewScenario);

    // message label 2
    lblMsg2 = new WLabel();
    boxCreateScenario->addWidget(lblMsg2);



    // Scenario Content widgets
    // ==========================
    boxScenarioContent = new WGroupBox("Scenario Transactions");
    gridLayout->addWidget(boxScenarioContent, 0, 1);


    // Setting the grid stretch factors
    gridLayout->setColumnStretch(1,1);
}

// event handler for the current scenario combo box
void US_ForecastGUI::listScenarios_Changed() {
    string selectedScenario = listScenarios->currentText().toUTF8();
    // TODO: fetch selected scenario from the database & update target balance & date
}

// update the current scenario's target balance and date
void US_ForecastGUI::btnUpdateBalanceAndDate_Click() {


    // parse balance from widget
    double balance;
    try {
        string strBalance = txtTargetBalance->text().toUTF8();
        balance = boost::lexical_cast<double>(strBalance);
    } catch(std::exception &e) {
        lblMsg1->setText("Target Balance must be a number!");
        lblMsg1->setStyleClass("error");
        return;
    }

    WDate targetDate = deTargetDate->date();

    // TODO: set values in database
    lblMsg1->setText("Success!");
    lblMsg1->setStyleClass("message");
}

// create a new scenario
void US_ForecastGUI::btnCreateNewScenario_Click() {
    string scenarioName = txtNewScenario->text().toUTF8();

    // parse scenario cost from widget
    double scenarioCost;
    try {
        string strScenarioCost = txtNewScenarioCost->text().toUTF8();
        scenarioCost = boost::lexical_cast<double>(strScenarioCost);
    } catch(std::exception &e) {
        lblMsg2->setText("New Scenario Cost must be a number!");
        lblMsg2->setStyleClass("error");
        return;
    }

    WDate startDate = deNewStartDate->date();
    WDate targetDate = deNewTargetDate->date();

    // TODO: insert into database via Project constructor call
    lblMsg2->setText("Success!");
    lblMsg2->setStyleClass("message");
}