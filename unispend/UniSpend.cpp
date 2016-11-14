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
#include <Wt/WEnvironment>
#include <Wt/WBootstrapTheme>

#include "US_Login.h"
#include "US_Workspace.h"

using namespace std;
using namespace Wt;

WApplication *createApplication(const WEnvironment& env) {
    WApplication *app = new WApplication(env);

    // Configure set up of the application instance
    app->setTitle("UniSpend");
    app->useStyleSheet("resources/unispend.css");
    app->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");

    // Setting the application theme
    Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(app);
    bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
    bootstrapTheme->setResponsive(true);
    app->setTheme(bootstrapTheme);

    // Create the main stack that contains the login and workspace containers
    WStackedWidget *mainStack = new WStackedWidget();

    // Create the login container
    US_Login *loginContainer = new US_Login(mainStack);
    mainStack->addWidget(loginContainer);

    // Create the workspace container
    US_Workspace *workspaceContainer = new US_Workspace(mainStack);
    mainStack->addWidget(workspaceContainer);

    // add the main stack widget to the root page
    app->root()->addWidget(mainStack);

    return app;
}

int main(int argc, char **argv) {
    return WRun(argc, argv, &createApplication);
}
