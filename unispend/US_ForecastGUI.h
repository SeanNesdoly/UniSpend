/*
 * Class       : US_ForecastGUI.h
 * Description : Container for the forecasting tab.
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WComboBox>

using namespace Wt;

class US_ForecastGUI : public WContainerWidget {
public:
    US_ForecastGUI(WContainerWidget *parent);
private:
    WComboBox *scenarioList;
};