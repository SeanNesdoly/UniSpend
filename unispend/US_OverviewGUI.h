//
// Created by Ryan Fredrickson on 2016-11-17.
//
#pragma once
#include <ctime>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
#include <Wt/Chart/WPieChart>
#include <Wt/Chart/WCartesianChart>
#include <Wt/WStandardItemModel>
#include <numeric>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WDateEdit>
#include <Wt/WDate>
#include <Wt/WPushButton>
#include <algorithm>
#include "US_User.h"
#include "US_Workspace.h"
#include <Wt/WAbstractItemView>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WTableView>
#include <Wt/Chart/WDataSeries>

using namespace Wt;
using namespace std;
class US_OverviewGUI : public WContainerWidget{
public:
    US_OverviewGUI(US_Workspace *parent);
private:
    User* _user;
    void btnSave_Click();
    Wt::Chart::WPieChart* piech;
    Wt::Chart::WCartesianChart* barch;
    Wt::Chart::WCartesianChart* scatch;
    Wt::Chart::WDataSeries* series;
    WStandardItemModel* model;
    WLabel* lblStartDate;
    WLabel* lblEndDate;
    WLabel* lblMsg;
    WDateEdit* StartDate;
    WDateEdit* EndDate;
    WHBoxLayout* overhbox;
    WVBoxLayout* Lvbox;
    WVBoxLayout* Rvbox;
    WHBoxLayout* datehbox;
    WPushButton* btnSave;
};