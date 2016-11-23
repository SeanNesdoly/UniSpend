//
// Created by Ryan Fredrickson on 2016-11-17.
//
#pragma once
#include <ctime>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
using namespace Wt;

class US_OverviewGUI : public WContainerWidget{
public:
    US_OverviewGUI(WContainerWidget *parent);
private:
    WLabel* startDate;
    WLabel* currentDate;
};


