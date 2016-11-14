/*
 * Class       : US_Login.cpp
 * Description : Login container that serves as the initial entrance to the application.
 * Author      : srnesdoly
 * Date        : 2016-11-11
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>

using namespace std;
using namespace Wt;

class US_Login : public WContainerWidget
{
public:
    US_Login(WContainerWidget *parent);

    void handleInternalPath(const string &internalPath);

private:
    void showWorkspace(); // show the main workspace container
};