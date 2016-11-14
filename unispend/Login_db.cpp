/*	
 * Class       : LogIn_db.cpp	
 * Description : Implementation of database editing .	
 * Author      : Yumou	
 * Date        : 2016-11-13
 *
 * Team lovelace	
 * CISC 320 Fall 2016	
 */
#include <Wt/Dbo/Dbo>
#include <string>
#include "Wt/Auth/Dbo/UserDatabase"

using namespace Wt;
namespace dbo = Wt::Dbo;

class User {
public:
   
    std::string name;
    std::string password;  

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name,     "name");
        dbo::field(a, password, "password");          
    }
};

void SignIn()
{
    /*
     * Setup a session, would typically be done once at application startup.
     */
    dbo::backend::Sqlite3 sqlite3("US_Database.db"); //select database "US_Database"
    dbo::Session session;
    session.setConnection(sqlite3);	
	session.mapClass<User>("users"); //select table "users"
    /*
     * Try to create the schema (will fail if already exists).
     */
    session.createTables();
	dbo::Transaction transaction(session);

    User *user = new User();
    user->name = "USER1"; 		/** will take from front**/
    user->password = "";		/** will take from front**/

    dbo::ptr<User> userPtr = session.add(user);
}

void LogIn(){
	dbo::backend::Sqlite3 sqlite3("US_Database.db"); //select database "US_Database"
    dbo::Session session;
    session.setConnection(sqlite3);	
	session.mapClass<User>("users"); //select table "users"
    session.createTables();
	dbo::Transaction transaction(session);	
	
	dbo::ptr<User> user1 = session.find<User>().where("name = ?").bind("USER1");/**user1 will take from front**/
	if(InputPW == user1->password)
		cout << "Login sucess"/** send a message to the front**/
	else
		cout << "Login failed"/**send a message to the front**/
	
}