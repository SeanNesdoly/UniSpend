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

US_ForecastGUI::US_ForecastGUI(US_Workspace *parent):
        WContainerWidget(parent)
{
    // retrieve the global user object from the parent workspace container
    _user = parent->user;

    setStyleClass("forecasting");

    // Forecasting tab layout
    hbox = new WHBoxLayout();
    this->setLayout(hbox);

    divLeft = new WContainerWidget();
    hbox->addWidget(divLeft);

    // ================================
    // Forecasting Parameter widgets
    // ================================
    boxForecastParams = new WGroupBox("Forecasting Parameters");
    divLeft->addWidget(boxForecastParams);

    // current scenario selection
    lblScenario = new WLabel("Current Scenario:");
    listScenarios = new WComboBox();
    // TODO: get scenarios!

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



    // =======================
    // New Scenario widgets
    // =======================
    boxCreateScenario = new WGroupBox("Create a New Scenario");
    divLeft->addWidget(boxCreateScenario);

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



    // ==========================
    // Scenario Content widgets
    // ==========================
    boxScenarioContent = new WGroupBox("Scenario Transactions");
    hbox->addWidget(boxScenarioContent, 1); // add section to tab container

    lblScenarioRange = new WLabel("<b>Scenario Transactions in the Range: </b>"); // TODO: add in scenario date range
    boxScenarioContent->addWidget(lblScenarioRange);

    tblScenarioData = new WTable();
    tblScenarioData->setHeaderCount(1);
    tblScenarioData->setWidth(Wt::WLength("100%"));

    // stlying table
    tblScenarioData->addStyleClass("table form-inline");
    tblScenarioData->addStyleClass("table-bordered");
    tblScenarioData->addStyleClass("table-hover");
    tblScenarioData->addStyleClass("table-striped");

    // header row
    vector<string> headerRowVals = {"Name", "Type", "Value ($)", "Date (yyyy-mm-dd)"};
    int numTransactions = 20; // TODO: replace
    int numCols = headerRowVals.size(); // name | type | value | date
    for (int row = 0; row < numTransactions; row++) {
        for (int col = 0; col < numCols; col++) {
            WText *cell = new WText();

            if (row == 0) {
                cell->setText(headerRowVals.at(col));
            } else {
                cell->setText("Item " + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col));
            }

            tblScenarioData->elementAt(row, col)->addWidget(cell);
        }
    }

    boxScenarioContent->addWidget(tblScenarioData);

    /*tblScenarioData = new WTableView();
    tblScenarioData->setAlternatingRowColors(true);
    tblScenarioData->setSelectionMode(Wt::NoSelection);
    tblScenarioData->setSortingEnabled(true);
    tblScenarioData->setHeaderHeight(0);
    tblScenarioData->setModel(parent->modelForecastingData);
    hbox->addWidget(tblScenarioData, 1);*/



    // ==========================
    // Scenario Analysis widgets
    // ==========================
    boxScenarioAnalysis = new WGroupBox("Scenario Analysis");
    hbox->addWidget(boxScenarioAnalysis);

    // progress bar for money spent @ target date
    //lblMoneySpent = new WLabel("<b>Current $ allocation towards target balance:</b>");
    barMoneySpent = new WProgressBar();
    barMoneySpent->setFormat("Leftover $ towards target balance %.0f %%");
    barMoneySpent->resize(Wt::WLength("100%"),100);
    barMoneySpent->setRange(0,100); // TODO: from database
    barMoneySpent->setValue(69); // TODO: from database
    boxScenarioAnalysis->addWidget(barMoneySpent);

    // leftover amount after scenario
    lblLeftover = new WLabel("$ left over to date:");
    txtLeftover = new WLineEdit();
    txtLeftover->setEnabled(false);
    txtLeftover->setText("$ LEFTOVER"); // TODO: from database
    lblLeftover->setBuddy(txtLeftover);
    boxScenarioAnalysis->addWidget(lblLeftover);
    boxScenarioAnalysis->addWidget(txtLeftover);

    // average spending with scenario costs applied
    lblSpendingWithScenario = new WLabel("Average ($/day) during school year:");
    txtSpendingWithScenario = new WLineEdit();
    txtSpendingWithScenario->setEnabled(false);
    txtSpendingWithScenario->setText("$ AVG_SPENDING_WITH_SCENARIO");
    lblSpendingWithScenario->setBuddy(txtSpendingWithScenario);
    boxScenarioAnalysis->addWidget(lblSpendingWithScenario);
    boxScenarioAnalysis->addWidget(txtSpendingWithScenario);

    // average spending WITHOUT scenario costs applied
    lblSpendingWithoutScenario = new WLabel("Average ($/day) since addition of Scenario:"); // TODO: scenario name
    txtSpendingWithoutScenario = new WLineEdit();
    txtSpendingWithoutScenario->setEnabled(false);
    txtSpendingWithoutScenario->setText("$ AVG_SPENDING_WITHOUT_SCENARIO");
    lblSpendingWithoutScenario->setBuddy(txtSpendingWithoutScenario);
    boxScenarioAnalysis->addWidget(lblSpendingWithoutScenario);
    boxScenarioAnalysis->addWidget(txtSpendingWithoutScenario);
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

    WDate targetDate = deNewTargetDate->date();

    // TODO: insert into database via Project constructor call
    lblMsg2->setText("Success!");
    lblMsg2->setStyleClass("message");
}