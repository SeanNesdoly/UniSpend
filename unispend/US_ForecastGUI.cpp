/*
 * Class       : US_ForecastGUI.cpp
 * Description : Implementation of the forecasting container.
 * Author      : srnesdoly
 * Date        : 2016-11-22
 *
 * Team lovelace
 * CISC 320 Fall 2016
 */

#include "US_ForecastGUI.h"

US_ForecastGUI::US_ForecastGUI(WContainerWidget *parent):
        WContainerWidget(parent)
{
    setStyleClass("forecast");

    scenarioList = new WComboBox();
    addWidget(scenarioList);
}