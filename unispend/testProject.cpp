#include <iostream>
#include "US_Project.h"

int main() {
    US_Project mainProject("brentlommen","main");
    //US_Transaction milkTransaction("brentlommen", "KFC", "groceries", 10.58 , "2016-09-11", "1", "main");
    //US_Transaction eggTransaction ("brentlommen", "carrots", "groceries", 3.99, "2016-10-20","1","main");
    //mainProject.addTransaction(milkTransaction);
    //mainProject.addTransaction(eggTransaction);
    vector<US_Transaction> mainTransactions;
    mainTransactions = mainProject.getAllTransactions("brentlommen", "Main");
    for(unsigned int i=0; i <= mainTransactions.size()-1; i++){
    	cout << mainTransactions.at(i).getName() << endl;
    }
    cout << mainProject.sumAllTransactions(mainTransactions) << endl;
    cout << mainProject.getCurrentBalance() << endl;

    //US_Project scenariProject("brentlommen", "plane tickets", 425.93, "2016-11-21", "2017-02-15");
    return 0;
}

