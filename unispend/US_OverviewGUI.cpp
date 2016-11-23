//
// Created by Ryan Fredrickson on 2016-11-17.
//

#include "US_OverviewGUI.h"

US_OverviewGUI::US_OverviewGUI(WContainerWidget *parent):
        WContainerWidget(parent)
{
    //Set Style
    setStyleClass("overview");
    //Get current and start date
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int currentDyear= now->tm_year+1900;
    int currentDmonth= now->tm_mon+1;
    int currentDday= now->tm_mday;
    int startDday=currentDday;
    if (currentDmonth==1){
        int startDyear=currentDyear-1;
        int startDmonth=12;
    }
    else{
        int startDyear=currentDyear;
        int startDmonth=currentDmonth;
    }

    //Show start and end date
    startDate = new WLabel("Start Date:", this);
    currentDate = new WLabel("End Date:", this);
    addWidget(startDate);
    addWidget(currentDate);

}
