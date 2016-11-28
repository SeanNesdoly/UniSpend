/*
 * Class       : US_SettingsGUI.cpp
 * Description : Implementation of the settings container
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include "US_SettingsGUI.h"


US_SettingsGUI::US_SettingsGUI(US_Workspace *parent)
{
    // retrieve the global user object from the parent workspace container
    workspace = parent;
    _user = workspace->user;

    setStyleClass("settings");
    hbox_root = new WHBoxLayout();
    this->setLayout(hbox_root);


    divSettings = new WContainerWidget();
    hbox_root->addWidget(divSettings);

    // ===============================
    // Project-level Settings Section
    // ===============================
    boxProjectSettings = new WGroupBox("Project Settings");
    divSettings->addWidget(boxProjectSettings);

    // main project starting balance
    lblStartBalance = new WLabel("Budget for the School Year:");
    txtStartBalance = new WLineEdit();
    txtStartBalance->setEmptyText("initial account balance on project start date");
    lblStartBalance->setBuddy(txtStartBalance);
    boxProjectSettings->addWidget(lblStartBalance);
    boxProjectSettings->addWidget(txtStartBalance);

    // save project settings
    btnSaveProjectSettings = new WPushButton("Update Starting Balance");
    btnSaveProjectSettings->clicked().connect(this, &US_SettingsGUI::btnSaveProjectSettings_Click);
    boxProjectSettings->addWidget(btnSaveProjectSettings);

    // user feedback on project settings
    lblMsgProject = new WLabel();
    boxProjectSettings->addWidget(lblMsgProject);



    // =============================
    // User-level Settings Section
    // =============================
    boxUserSettings = new WGroupBox("User Settings");
    divSettings->addWidget(boxUserSettings);

    // password label & field
    lblPassword = new WLabel("New Password:");
    txtPassword = new WLineEdit();
    txtPassword->setEmptyText("update the existing password");
    txtPassword->setEchoMode(WLineEdit::EchoMode::Password);
    lblPassword->setBuddy(txtPassword);
    boxUserSettings->addWidget(lblPassword);
    boxUserSettings->addWidget(txtPassword);

    // confirmation of new password
    lblConfirmPassword = new WLabel("Confirm New Password:");
    txtConfirmPassword = new WLineEdit();
    txtConfirmPassword->setEchoMode(WLineEdit::EchoMode::Password);
    lblConfirmPassword->setBuddy(txtConfirmPassword);
    boxUserSettings->addWidget(lblConfirmPassword);
    boxUserSettings->addWidget(txtConfirmPassword);

    // fist name of user
    lblFirstName = new WLabel("Set First Name:");
    txtFirstName = new WLineEdit();
    lblFirstName->setBuddy(txtFirstName);
    boxUserSettings->addWidget(lblFirstName);
    boxUserSettings->addWidget(txtFirstName);

    // last name of user
    lblLastName = new WLabel("Set Last Name:");
    txtLastName = new WLineEdit();
    lblLastName->setBuddy(txtLastName);
    boxUserSettings->addWidget(lblLastName);
    boxUserSettings->addWidget(txtLastName);

    // save user settings
    btnSaveUserSettings = new WPushButton("Update User Settings");
    btnSaveUserSettings->clicked().connect(this, &US_SettingsGUI::btnSaveUserSettings_Click);
    boxUserSettings->addWidget(btnSaveUserSettings);

    // user feedback on user settings
    lblMsgUser = new WLabel();
    boxUserSettings->addWidget(lblMsgUser);



    // ==================================
    // Recurring Transactions Table
    // ==================================
    boxTable = new WGroupBox("Recurring Transactions");
    hbox_root->addWidget(boxTable, 1);

    // table initialization
    tblRecurringCosts = new WTable();
    tblRecurringCosts->setHeaderCount(1);
    tblRecurringCosts->setWidth(Wt::WLength("100%"));

    // stlying table
    tblRecurringCosts->addStyleClass("table form-inline");
    tblRecurringCosts->addStyleClass("table-bordered");
    tblRecurringCosts->addStyleClass("table-hover");
    tblRecurringCosts->addStyleClass("table-striped");

    populateTable(); // populates the table from the database with recurring transactions!

//    tblRecurringCosts->setAlternatingRowColors(true);
//    tblRecurringCosts->setSelectionMode(Wt::SingleSelection);
//    tblRecurringCosts->setSortingEnabled(true);
//    tblRecurringCosts->setHeaderHeight(0);
//    tblRecurringCosts->setModel(parent->modelRecurringTransactionData);
    boxTable->addWidget(tblRecurringCosts);



    // ==================================
    // Add Recurring Transactions Section
    // ==================================
    boxAddTransaction = new WGroupBox("Add Recurring Transaction");
    hbox_root->addWidget(boxAddTransaction);

    // name
    lblName = new WLabel("Name of Transaction:");
    txtName = new WLineEdit();
    lblName->setBuddy(txtName);
    boxAddTransaction->addWidget(lblName);
    boxAddTransaction->addWidget(txtName);

    // type
    lblType = new WLabel("Type:");
    txtType = new WLineEdit();
    lblType->setBuddy(txtType);
    boxAddTransaction->addWidget(lblType);
    boxAddTransaction->addWidget(txtType);

    // value
    lblValue = new WLabel("Value ($):");
    txtValue = new WLineEdit();
    lblValue->setBuddy(txtValue);
    boxAddTransaction->addWidget(lblValue);
    boxAddTransaction->addWidget(txtValue);

    // date
    lblDate = new WLabel("Date of First Transaction:");
    deDate = new WDateEdit();
    deDate->setFormat("yyyy-MM-dd");
    deDate->setDate(WDate::currentServerDate());
    lblDate->setBuddy(deDate);
    boxAddTransaction->addWidget(lblDate);
    boxAddTransaction->addWidget(deDate);

    // frequency
    lblFrequency = new WLabel("Frequency:");
    ddFrequency = new WComboBox();
    ddFrequency->addItem("daily");
    ddFrequency->addItem("weekly");
    ddFrequency->addItem("monthly");
    ddFrequency->addItem("yearly");
    lblFrequency->setBuddy(ddFrequency);
    boxAddTransaction->addWidget(lblFrequency);
    boxAddTransaction->addWidget(ddFrequency);

    // number of repeats
    lblNumRepeats = new WLabel("Number of Repeats:");
    spinNumRepeats = new WSpinBox();
    spinNumRepeats->setMinimum(1);
    spinNumRepeats->setSingleStep(1);
    lblNumRepeats->setBuddy(spinNumRepeats);
    boxAddTransaction->addWidget(lblNumRepeats);
    boxAddTransaction->addWidget(spinNumRepeats);

    // add transaction button
    btnAddTransaction = new WPushButton("Add Recurring Transaction");
    btnAddTransaction->clicked().connect(this, &US_SettingsGUI::btnAddTransaction_Click);
    boxAddTransaction->addWidget(btnAddTransaction);

    // user feedback
    lblMsgTransaction = new WLabel();
    boxAddTransaction->addWidget(lblMsgTransaction);
}

// populate the recurring transactions table
void US_SettingsGUI::populateTable() {
    if (_user != nullptr) {
        vector<US_Transaction> allTransactions = _user->getMain().getAllTransactions();
        US_Transaction *currTransaction = nullptr;


        vector<string> headerRowVals = {"Name", "Type", "Value ($)", "Start Date (yyyy-mm-dd)", "Frequency", "# of Repeats", "Delete"};
        int numTransactions = allTransactions.size();// TODO: replace
        int numCols = headerRowVals.size(); // name | type | value | date | frequency | number of repeats | delete
        for (int row = 0; row < numTransactions; row++) {

            if (row != 0) {
                // update the current transaction for the row
                currTransaction = &allTransactions.at(row - 1);
            }

            for (int col = 0; col < numCols; col++) {
                if (col < (numCols - 1)) {
                    WText *cell = new WText();

                    if (row == 0) {
                        cell->setText(headerRowVals.at(col));
                    } else {

                        // set the cells text
                        switch(col) {
                            case 0 :
                                cell->setText(currTransaction->getName());
                                break;
                            case 1 :
                                cell->setText(currTransaction->getType());
                                break;
                            case 2 :
                                cell->setText(boost::lexical_cast<std::string>(currTransaction->getValue()));
                                break;
                            case 3 :
                                cell->setText(currTransaction->getDate());
                                break;
                            default: cell->setText("Item " + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col));
                        }
                    }

                    // add the cell to the table
                    tblRecurringCosts->elementAt(row, col)->addWidget(cell);
                } else {
                    if (row != 0) {
                        // delete icon
                        WImage* imgDelete = new WImage("resources/delete.png");
                        imgDelete->setAttributeValue("row", boost::lexical_cast<std::string>(row));
                        imgDelete->clicked().connect(std::bind([=] () {
                            WTableRow* theRow = tblRecurringCosts->rowAt(boost::lexical_cast<int>(imgDelete->attributeValue("row")));
                            theRow->hide();
                            //string name = boost::lexical_cast<string>(theRow->elementAt(0)->widget(0)).text().toUTF8();
                            //string type = boost::lexical_cast<string>(theRow->elementAt(0)->widget(0)).text().toUTF8();
                            // TODO: delete in database


                        }));

                        tblRecurringCosts->elementAt(row, col)->addWidget(imgDelete);
                    }
                }
            }
        }
    }
}


// event listener to save currently set project settings
void US_SettingsGUI::btnSaveProjectSettings_Click() {
    // parse starting balance from widget
    double startingBalance;
    try {
        string strStartingBalance = txtStartBalance->text().toUTF8();
        startingBalance = boost::lexical_cast<double>(strStartingBalance);
    } catch(std::exception &e) {
        lblMsgProject->setText("Starting Balance must be a number!");
        lblMsgProject->setStyleClass("error");
        return;
    }

    // Update the yearly balance
    _user->updateBalance(startingBalance);

    this->workspace->currentBalance->setText("Balance on " + WDate::currentDate().toString().toUTF8() + ": " + boost::lexical_cast<std::string>(_user->getMain().getCurrentBalance()));

    cout << "MAIN PROJECT: " << endl;
    cout << "Get current monthly allowance: " << endl;
    cout << _user->getMain().getMonthlyAllowance() << endl;

    lblMsgProject->setText("Success!");
    lblMsgProject->setStyleClass("message");
}

// event listener to save currently set user settings
void US_SettingsGUI::btnSaveUserSettings_Click() {
    bool failure = false;

    string pass = txtPassword->text().toUTF8();
    string confirmPass = txtConfirmPassword->text().toUTF8();
    if (pass != confirmPass) {
        lblMsgUser->setText("Passwords do not match!");
        lblMsgUser->setStyleClass("error");
        failure = true;
    }

    string fName = txtFirstName->text().toUTF8();
    string lName = txtLastName->text().toUTF8();

    if (!failure) {
        try
        {
            if (pass.size() != 0)
            {
            
                // Update the password
                _user->setPassword(pass);
            }
            
            if (fName.size() != 0)
            {
                // Update the first name
                _user->setFirstName(fName);
            }

            if (lName.size() != 0)
            {
                // Update the last name
                _user->setLastName(lName);
            }
           // If got here - values successfully updated
           lblMsgUser->setText("Success!");
           lblMsgUser->setStyleClass("message");
        } catch (UserException& e)
        {
            lblMsgUser->setText(e.what());
            lblMsgUser->setStyleClass("message");
            cout << e.what() << endl;
        }
    }
}

// Adds in a recurring transaction to the database
void US_SettingsGUI::btnAddTransaction_Click() {
    string name = txtName->text().toUTF8();
    string type = txtType->text().toUTF8();

    // parse transaction value from widget
    double value;
    try {
        string strValue = txtValue->text().toUTF8();
        std::cout << strValue << std::endl;
        value = boost::lexical_cast<double>(strValue);
        std::cout << value << " DOUBLE VALUE" << std::endl;
    } catch(std::exception &e) {
        lblMsgTransaction->setText("Value must be a number!");
        lblMsgTransaction->setStyleClass("error");
        return;
    }

    string date = deDate->text().toUTF8();
    string frequency = ddFrequency->currentText().toUTF8();
    int numRepeats = spinNumRepeats->value();
    lblMsgTransaction->setStyleClass("error");
    if(name == "") {
        lblMsgTransaction->setText("Name of Transaction must not be blank!");
        return;
    }
    else if(type == "") {
        lblMsgTransaction->setText("Type must not be blank!");
        return;
    }
    else {
        _user->getMain().repeatTransaction(_user->getName(), name, type, value, date, "main", frequency, numRepeats);

        this->tblRecurringCosts->clear();
        populateTable(); // update the table
    }
}

