
#include <iostream>
#include "US_Project.h"
#include "US_User.h"
#include "US_Transaction.h"

int main() {
    try
    {

        User brent("brentl", "hello");
        cout << "You are logged into account with username " << brent.getName() << endl;
        bool flag = true;
        while(flag){
            cout << "choose an action\n "<<endl;
            cout << "1: add a transaction \n2: Delete a transaction \n3: get Average daily spending \n4: show monthly allowance \n5: show current ballance \n6: Reset Starting Balance \n7: Get Required rate "
                    "\n8: Test all getters for US_Project class \n9: Create a scenario \n10: Compare Average daily spending before and after creation of scenario. \n11: done Test " << endl;
            string command;
            cin >> command;
            int choice = atoi(command.c_str());


            switch(choice){
                case 1:{
        	    US_Transaction toAdd(brent.getName(), "mcDonalds", "fast food", 7.49, "2016-11-26", "0", "main");
                    brent.addTransaction(toAdd);
                    cout << "all transactions for username" << brent.getName() << endl;
                    for(int i=0; i < brent.getMain().getTransactions().size(); i++){
                    	cout << brent.getMain().getTransactions().at(i).getName() << " , "; 
                    }
                    cout << endl;
                    break;
                }
                case 2:{
                    cout << "Deleting transaction: " << brent.getMain().getTransactions().at(0).getName() << " from main project." << endl;
                    US_Transaction toDelete(brent.getMain().getTransactions().at(0));
                    brent.deleteTransaction(toDelete);
                    cout << "all transactions for username" << brent.getName() << endl;
                    for(int i=0; i < brent.getMain().getTransactions().size(); i++){
                        cout << brent.getMain().getTransactions().at(i).getName() << " , ";
                    }
                    cout << endl;
                    break;
                }
                case 3:{
                    cout << "Calaculating you average daily spending." << endl;
                    double average = brent.getMain().getAverage(brent.getMain().getTransactions());
                    cout << "you spend an average of: $" << average <<"/day calculated from " << brent.getMain().getStartDate() << " till today" << endl;
                    break;
                }
                case 4:{
                    cout << "this is your remaining monthly allowance " << brent.getMain().getMonthlyAllowance() << endl;
                    break;
                }
                case 5:{
                    cout << "this is your current balance " << brent.getMain().getCurrentBalance() << endl;
                    break;
                }
                case 6:{
                    cout << "what would you like your new balance to be? " << endl;
                    double newBalance;
                    cin >> newBalance;
                    brent.updateBalance(newBalance);
                    break;
                }
                case 7:{
                    cout << "you can spend $" << brent.getMain().getRequiredRate() << "/day in order to survive the school year with your remaining " << brent.getMain().getCurrentBalance() << " From your starting balance of " << brent.getMain().getYearBalance() << endl;
                    break;
                }
                case 8:{
                     cout << "ID: " << brent.getMain().getId() << "\nUsername: " << brent.getMain().getUsername() << "\nProjectName: " << brent.getMain().getProjectName() << "\nYear Balance: " << brent.getMain().getYearBalance() << endl;
                     break;
                }
                case 9:{
                    cout << "Creating a scenario called Vacation whith a predicted cost of $600 with a target date of 2017-02-25." << endl;
                    US_Project newScenario(brent.getName(), "Vacation", 600, "2017-02-25");
                    vector<US_Project> test = brent.getScenarios();
                    test.push_back(newScenario);
                    brent.setScenarioVector(test);
                    cout << "\nAll scenarios for user" << brent.getName() << endl;
                    for(int i=0; i < brent.getScenarios().size(); i++){
                        cout << brent.getScenarios().at(i).getProjectName() << " , ";
                    }
                    cout << endl;
                    break;
                }
                case 10:{
                    cout << "your average daily spending is $" << brent.getMain().getAverage(brent.getMain().getTransactions()) << "/day" << endl;
                    cout << "your average daily spending since you started saving for " << brent.getScenarios().at(0).getProjectName() << " is $" << brent.getScenarios().at(0).getAverage(brent.getScenarios().at(0).getTransactions()) << "/day" << endl;
                    break;
                }
                case 11:{
                    cout << "Testing complete." << endl;
                    flag = false;
                }
            }
        }

        //brent.updateBalance(5000);
        //double requiredRate1 = brent.getMain().getRequiredRate();
        //cout << "You will need to spend less than " << requiredRate1 <<"/day in order to afford your scenario which costs " << brent.getScenarios().at(0).getScenarioCost() << endl;
        /*
	brent.getMain().repeatTransaction(brent.getName(), "fish", "Groceries", 10, "2016-11-26", "main", "weekly", 4);
	brent.getMain().repeatTransaction(brent.getName(), "things", "stuff", 10000, "2016-09-15", "main", "yearly", 4);
	brent.getMain().repeatTransaction(brent.getName(), "beers", "Alcohol", 40, "2016-10-13", "main", "monthly", 4);
	brent.getMain().repeatTransaction(brent.getName(), "payment", "car", 1000, "2016-03-30", "main", "daily", 4);
        */
        //US_Transaction transTest(brent.getName(), "fish", "Groceries", 10, "2016-11-25", "0", "main");
        //brent.addTransaction(transTest);


        /*
        US_Transaction toDelete = brent.getMain().getTransactions().at(0);
        cout << "Transaction: " << brent.getMain().getTransactions().at(0).getName() << " was deleted! " << endl;
        brent.deleteTransaction(toDelete);
        for(int i=0; i < brent.getMain().getTransactions().size(); i++){
        	cout << "Main: " << brent.getMain().getTransactions().at(i).getName() << endl;
        }

        for(int i=0; i < brent.getScenarios().size(); i++){
                for(int j=0; j < brent.getScenarios().at(i).getTransactions().size(); j++){
                	cout << "Scenario: " << brent.getScenarios().at(i).getProjectName() << " Transaction: " << brent.getScenarios().at(i).getTransactions().at(j).getName() << endl;
                }
        }
        */

        // Create one transaction and add to main project
        //US_Transaction transTest(brent.getName(), "testUserAdd", "Groceries", 10.0, "2016-11-24", "0", "main");
        
        //brent.addTransaction(transTest);
        // Create a new scenario
        //US_Project newScenario(brent.getName(), "testScenario2", 26.0, "2016-11-30");
        //vector<US_Project> test = brent.getScenarios();
        //test.push_back(newScenario);
        //brent.setScenarioVector(test);
        //cout << brent.getScenarios().size() << endl;
        //cout << brent.getScenarios().at().getScenarioCost() << endl;
        // Add transactions to scenario
        //vector<US_Transaction> allTrans = brent.getMain().getAllTransactions();
        //for(int i=0; i < allTrans.size(); i++){
       // 	cout << allTrans.at(i).getName();
        //}
    } catch (UserException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

