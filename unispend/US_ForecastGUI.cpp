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
    listScenarios->addItem("");
    for(int i=0; i < _user->getScenarios().size(); i++){
    	listScenarios->addItem(_user->getScenarios().at(i).getProjectName());
    }
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
    boxScenarioAnalysis->addWidget(barMoneySpent);

    // leftover amount after scenario
    lblLeftover = new WLabel("$ left over to date:");
    txtLeftover = new WLineEdit();
    double leftover = _user->getMain().getRemainder();
    txtLeftover->setText("$" + boost::lexical_cast<string>(leftover));
    txtLeftover->setEnabled(false);
    lblLeftover->setBuddy(txtLeftover);
    boxScenarioAnalysis->addWidget(lblLeftover);
    boxScenarioAnalysis->addWidget(txtLeftover);

    // average spending with scenario costs applied
    lblSpendingWithScenario = new WLabel("Average ($/day) during school year:");
    txtSpendingWithScenario = new WLineEdit();
    txtSpendingWithScenario->setEnabled(false);
    vector<US_Transaction> mainTransactions = _user->getMain().getTransactions();
    double mainDailySpending = _user->getMain().getAverage(mainTransactions);
    std::ostringstream mainDailySpendingStr;
    mainDailySpendingStr << mainDailySpending;

    txtSpendingWithScenario->setText("$"+mainDailySpendingStr.str()+"/day");
    lblSpendingWithScenario->setBuddy(txtSpendingWithScenario);
    boxScenarioAnalysis->addWidget(lblSpendingWithScenario);
    boxScenarioAnalysis->addWidget(txtSpendingWithScenario);

    // average spending WITHOUT scenario costs applied
    lblSpendingWithoutScenario = new WLabel("Average ($/day) since planning for Scenario:"); // TODO: scenario name
    txtSpendingWithoutScenario = new WLineEdit();
    txtSpendingWithoutScenario->setEnabled(false);
    txtSpendingWithoutScenario->setText("$ AVG_SPENDING_WITHOUT_SCENARIO");
    lblSpendingWithoutScenario->setBuddy(txtSpendingWithoutScenario);
    boxScenarioAnalysis->addWidget(lblSpendingWithoutScenario);
    boxScenarioAnalysis->addWidget(txtSpendingWithoutScenario);
}

// event handler for the current scenario combo box
void US_ForecastGUI::listScenarios_Changed() {
    vector<US_Transaction> scenarioTransactions;
    string selectedScenario = listScenarios->currentText().toUTF8();
    for(int i=0; i < _user->getScenarios().size(); i++){
    	if(_user->getScenarios().at(i).getProjectName() == selectedScenario){
             scenarioTransactions = _user->getScenarios().at(i).getTransactions();
             double scenarioDailySpending = _user->getScenarios().at(i).getAverage(scenarioTransactions);
             std::ostringstream scenarioDailySpendingStr;
             scenarioDailySpendingStr << scenarioDailySpending;
             txtSpendingWithoutScenario->setText("$"+scenarioDailySpendingStr.str()+"/day");

             double scenarioCost = _user->getScenarios().at(i).getScenarioCost();
             double moneyLeftover = _user->getMain().getRemainder();
             barMoneySpent->setRange(0,scenarioCost);
             barMoneySpent->setValue(moneyLeftover);
             lblScenarioRange->setText( "<b>" + _user->getScenarios().at(i).getProjectName() + "</b>" + "<b> Transactions in the Range: </b>" + _user->getScenarios().at(i).getStartDate() +" - "+ _user->getScenarios().at(i).getTargetDate());

             boxScenarioContent->setTitle(_user->getScenarios().at(i).getProjectName() + " Transactions");
             lblSpendingWithoutScenario->setText("Average ($/day) since planning for " + _user->getScenarios().at(i).getProjectName());
        }
    }
    tblScenarioData->clear();
    vector<string> headerRowVals = {"Name", "Type", "Value ($)", "Date (yyyy-mm-dd)"};

    int numTransactions = scenarioTransactions.size();
    int numCols = headerRowVals.size(); // name | type | value | date
    for (int row = 0; row <= numTransactions; row++) {
        for (int col = 0; col < numCols; col++) {
            WText *cell = new WText();

            if (row == 0) {
                cell->setText(headerRowVals.at(col));
            } else {
                switch(col){
                  case 0:{
                    cell->setText(scenarioTransactions.at(row-1).getName());
                    break;
                  }
                  case 1:{
                    cell->setText(scenarioTransactions.at(row-1).getType());
                    break;
                  }
                  case 2:{
                    string val = boost::lexical_cast<string>(scenarioTransactions.at(row-1).getValue());
                    cell->setText(val);
                    break;
                  }
                  case 3:{
                    cell->setText(scenarioTransactions.at(row-1).getDate());
                  }
                }
                //tblScenarioData->elementAt(row, col)->addWidget(cell);
            }
            tblScenarioData->elementAt(row, col)->addWidget(cell);
        }
    }

    boxScenarioContent->addWidget(tblScenarioData);

    // TODO: fetch selected scenario from the database & update target balance & date
}

// update the current scenario's target balance and date
void US_ForecastGUI::btnUpdateBalanceAndDate_Click() {
    // parse balance from widget
    double balance;
    string strBalance = txtTargetBalance->text().toUTF8();
    try {
        balance = boost::lexical_cast<double>(strBalance);
        string selectedScenario = listScenarios->currentText().toUTF8();
    } catch(std::exception &e) {
        lblMsg1->setText("Target Balance must be a number!");
        lblMsg1->setStyleClass("error");
    }

    string selectedScenario = listScenarios->currentText().toUTF8();
    WDate targetDate = deTargetDate->date();
    string strTargetDate = targetDate.toString("yyyy-MM-dd").toUTF8();
    WDate currentDate = WDate::currentServerDate();
    string strCurrentDate = currentDate.toString("yyyy-MM-dd").toUTF8();

    for(int i=0; i < _user->getScenarios().size(); i++){
            if(_user->getScenarios().at(i).getProjectName() == selectedScenario){
                if(strBalance != "" && strTargetDate != strCurrentDate ){
                    _user->getScenarios().at(i).setScenarioCost(balance);
                    _user->getScenarios().at(i).setTargetDate(strTargetDate);
                    lblScenarioRange->setText( "<b>" + _user->getScenarios().at(i).getProjectName() + "</b>" + "<b> Transactions in the Range: </b>" + _user->getScenarios().at(i).getStartDate() +" - "+strTargetDate);
                }else if(strBalance != "" && strTargetDate == strCurrentDate){
                    _user->getScenarios().at(i).setScenarioCost(balance);
                }else if(strBalance == "" && strTargetDate != strCurrentDate){
                    _user->getScenarios().at(i).setTargetDate(strTargetDate);
                    lblScenarioRange->setText( "<b>" + _user->getScenarios().at(i).getProjectName() + "</b>" + "<b> Transactions in the Range: </b>" + _user->getScenarios().at(i).getStartDate() +" - "+strTargetDate);
                    cout << "This should be the new date "<< _user->getScenarios().at(i).getTargetDate() << endl;
                }else{
                    lblMsg1->setText("new cost and target date need to be changed before updating");
                }

                double scenarioCost = _user->getScenarios().at(i).getScenarioCost();
                double moneyLeftover = _user->getMain().getLeftover();
                barMoneySpent->setRange(0,scenarioCost);
                barMoneySpent->setValue(moneyLeftover);
            }
    }



    // TODO: set values in database
    lblMsg1->setText("Success!");
    lblMsg1->setStyleClass("message");
}

// create a new scenario
void US_ForecastGUI::btnCreateNewScenario_Click() {
    string scenarioName = txtNewScenario->text().toUTF8();
    string strScenarioCost = txtNewScenarioCost->text().toUTF8();
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
    string strTargetDate = targetDate.toString("yyyy-MM-dd").toUTF8();


    US_Project newScenario(_user->getName(), scenarioName, scenarioCost, strTargetDate);
    listScenarios->addItem(scenarioName);

    // TODO: insert into database via Project constructor call
    lblMsg2->setText("Success!");
    lblMsg2->setStyleClass("message");
}
