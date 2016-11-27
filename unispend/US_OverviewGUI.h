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
using namespace Wt;

class US_OverviewGUI : public WContainerWidget{
public:
    US_OverviewGUI(WContainerWidget *parent);
private:
    void btnSave_Click();
    Wt::Chart::WPieChart* piech;
    Wt::Chart::WCartesianChart* barch;
    Wt::Chart::WCartesianChart* scatch;
    Wt::WContainerWidget* Rcont;
    WStandardItemModel* model;
    WLabel* lblStartDate;
    WLabel* lblEndDate;
    WDateEdit* StartDate;
    WDateEdit* EndDate;
    WHBoxLayout* overhbox;
    WVBoxLayout* Lvbox;
    WVBoxLayout* Rvbox;
    WHBoxLayout* datehbox;
    WPushButton* btnSave;
};