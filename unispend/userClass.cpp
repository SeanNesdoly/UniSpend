#include "userClass.h"

User::User(const string username, const string& pass) : name(username), password(pass)
{
    //create user in SQL
    cout << "Creating user with name: " << name << " pass: " << password << endl;
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
    string sqlCommand = "INSERT INTO `users` (`name`, `password`) VALUES ('" + name + "', '" + pass + "')";

    try
    {
       stmt->execute(sqlCommand);
       userExists = false;

    } catch(sql::SQLException e)
    {
        cout << endl << "User with name '" << name << "' already exists"  << endl;
        cout << "Please enter a new username and try again" << endl;
        userExists = true;
    }

    if (userExists == false)
    {
        cout << "Successfully created user with name " << name << endl;
    }

    delete stmt;
    delete con;

}

string& User::getName()
{
   return name;
}

string& User::getPassword()
{
    return password;
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
    string sqlCommand = "UPDATE `users` SET `password`='" + password +"' WHERE `name`='" + name + "'";
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
