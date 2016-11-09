/*
 * Class       : UniSpend.cpp
 * Description : Contains the main method for running the application and creating sessions.
 * Author      : srnesdoly
 * Date        : 2016-11-07
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include <Wt/WApplication>

using namespace std;
using namespace Wt;

WApplication *createApplication(const WEnvironment& env) {
    WApplication *app = new WApplication(env);

    // TESTING config file
    // string value;
    // app->readConfigurationProperty("appRoot", value);
    // app->setTitle(value);

    app->setTitle("UniSpend");

    return app;
}

int main(int argc, char **argv) {
    return WRun(argc, argv, &createApplication);

    //TODO: test running the app via WServer instantiation
    /*try {
        WServer server(argc, argv, WT_CONFIG_XML);
        server.addEntryPoint(Application, &createApplication);
        server.run();
    } catch (WServer::Exception& e) {
        std::cerr << e.what() << endl;
    } catch (exception &e) {
        std::cerr << "exception: " << e.what() << endl;
    }*/
}
