#include "US_User.h"

// Set exception class methods
UserException::UserException(const string& outputMsg): outputMsg(outputMsg)
{
	// No additional setup needed
}

string& UserException::what()
{
	return outputMsg;
}

// Sign up constructor
User::User(const string& username, const string& pass, const string& firstName, const string& lastName, double startBalance): name(username), password(pass), fName(firstName), lName(lastName)
{
    //try to create user in SQL
    cout << "Tryng to create user with username: " << name << " first name: " << fName << " last Name:  " << lName << " pass: " << password << endl;
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");

    // Try to insert the user into users table
    sql::ResultSet *res;
    bool userExists = false;
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    //string sqlCommand = "INSERT INTO `users` (`name`, `password`) VALUES ('" + name + "', '" + pass + "')";
    string sqlCommand = "INSERT INTO `users`(`username`, `password`, `FirstName`, `LastName`, `signUpDate`) VALUES ('" + name + "', '" + password + "', '" + fName + "', '" + lName + "', NOW())";

    try
    {
       stmt->execute(sqlCommand);
       userExists = false;

    } catch(sql::SQLException e)
    {
        userExists = true;
        throw UserException("Username already taken. Please try to use another username");
    }

    if (userExists == false)
    {
        cout << "Successfully created user with name " << name << endl;
        // Now that we have created user we need to initialize the US_Projects object and create the main project
        // By default we are saying user does not have a set budget since they specify this through settings to pass 0 to budget for month
        US_Project main(name, startBalance);
        this->mainProject = main;
        US_Project newScenario(name, "testScenario", 24.0, "2016-11-30");
        this->scenarioProjects.push_back(newScenario);
        res = stmt->executeQuery("SELECT NOW()");
        res->next();
        this->signUpDate = res->getString(1);

    }

    delete stmt;
    delete con;

}

// Login constructor
User::User(const string& username, const string& pass){
    // We need to first try to login to see if we can get the user
    // Then populate their info to all members of the object ie. firstname, lastname
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");    

    sql::ResultSet *res;
    bool userValid = false;
    
    // Connect to MySQL
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "SELECT * FROM `users` WHERE `username` = '" + username + "'"; 
    res = stmt->executeQuery(sqlCommand);
    if (res->next() == false){
        string errorStr = "User with username: " + username + " does not exist";
        throw UserException(errorStr);
    }
    else
    {
        // We need to check that both name and password match
        if(res->getString("username").compare(username) == 0 && res->getString("password").compare(pass) == 0)
        {
            // We populate the global variables for the object
            this->name = res->getString("username");
            this->password = res->getString("password");
            this->fName = res->getString("FirstName");
            this->lName = res->getString("LastName");
            US_Project main(res->getString("username"), "main");
            vector<US_Transaction> trans = main.getAllTransactions();
            main.setTransactions(trans);
    	    this->mainProject = main;
            vector<US_Project> scenProjects;
            sqlCommand = "SELECT * FROM `projects` WHERE `username` = '"+username+"' AND `projectName` != 'main'";
            res = stmt->executeQuery(sqlCommand);
            while(res->next())
            {
            	US_Project projectToAdd(username, res->getString("projectName"));
                vector<US_Transaction> toAdd = projectToAdd.getAllTransactions();
                projectToAdd.setTransactions(toAdd);
                scenProjects.push_back(projectToAdd);
            }
            this->scenarioProjects = scenProjects;
            cout << "Successfully logged in and populated all fields" << endl;
         } 
         else
         {
            throw UserException("Invalid login credentials.");
         }
    }
}


// method used to add a single transaction. adds to the transaction vector of the current project aswell as the SQL DB.
// when impllementing addTransaction we need to check if their are any existing projects for the user. if there is then we need to add transaction to main then add transaction to the project(s).
void User::addTransaction(US_Transaction newTransaction){

    this->mainProject.addTransaction(newTransaction);

    for(int i=0; i < scenarioProjects.size(); i++){
        newTransaction.setProjectName(scenarioProjects.at(i).getProjectName());
    	this->scenarioProjects.at(i).addTransaction(newTransaction);
    }
}

void User::deleteTransaction(US_Transaction oldTransaction){
    this->mainProject.deleteTransaction(oldTransaction);
    vector<US_Transaction> updated = this->mainProject.getAllTransactions();
    this->mainProject.setTransactions(updated);

    for(int i=0; i < scenarioProjects.size(); i++){
        oldTransaction.setProjectName(scenarioProjects.at(i).getProjectName());
        this->scenarioProjects.at(i).deleteTransaction(oldTransaction);
        vector<US_Transaction> updated = this->scenarioProjects.at(i).getAllTransactions();
        this->scenarioProjects.at(i).setTransactions(updated);
    }

}

void User::updateBalance(double balance){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "DELETE from `projects` WHERE `username` = '" +name+"' AND `projectName` = 'main'";
    stmt->execute(sqlCommand);
    US_Project newMain(name, balance);
    this->mainProject = newMain;
}


string& User::getName()
{
   return name;
}

string& User::getPassword()
{
    return password;
}

string& User::getFirstName()
{
    return fName;
}

string& User::getLastName()
{
    return lName;
}

void User::setPassword(const string& pass)
{
    password = pass;
    // Need to update for the user
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");

    // Try to retrieve results from the users table
    sql::ResultSet *res;
    bool userExists = false;
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "UPDATE `users` SET `password`='" + password +"' WHERE `username`='" + name + "'";
    try
    {
        stmt->execute(sqlCommand);
        cout << "Password changed successfully" << endl;
    } catch (sql::SQLException e)
    {
        cout << "Error happened. Password change has not been set" << endl;
    }
    
    delete stmt;
    delete con;
}


void User::setFirstName(const string& firstName)
{
    // Need to update for the user
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");

    // Try to retrieve results from the users table
    sql::ResultSet *res;
    bool userExists = false;
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "UPDATE `users` SET `FirstName`='" + firstName +"' WHERE `username`='" + name + "'";
    try
    {
        stmt->execute(sqlCommand);
        // Success so we update the global variable
        this->fName = firstName;
        cout << "First name changed successfully" << endl;
    } catch (sql::SQLException e)
    {
        cout << "Error happened. First Name change has not been set" << endl;
    }

    delete stmt;
    delete con;
}

void User::setLastName(const string& lastName)
{
    // Need to update for the user
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "lovelace320");

    // Try to retrieve results from the users table
    sql::ResultSet *res;
    bool userExists = false;
    stmt = con->createStatement();
    stmt->execute("USE US_Database");
    string sqlCommand = "UPDATE `users` SET `LastName`='" + lastName +"' WHERE `username`='" + name + "'";
    try
    {
        stmt->execute(sqlCommand);
        // Success so we update the global variable
        this->lName = lastName; 
        cout << "Last name changed successfully" << endl;
    } catch (sql::SQLException e)
    {
        cout << "Error happened. Last Name change has not been set" << endl;
    }

    delete stmt;
    delete con;   
}

US_Project User::getMain()
{
    return mainProject;
}

vector<US_Project> User::getScenarios()
{
    return scenarioProjects;
}

string User::getSignUpDate(){
    return signUpDate;
}


void User::setScenarioVector(vector<US_Project> scenList)
{
    scenarioProjects = scenList;
}

