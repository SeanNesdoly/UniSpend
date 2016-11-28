//
// Created by Ryan Fredrickson on 2016-11-17.
//
#include "US_OverviewGUI.h"

US_OverviewGUI::US_OverviewGUI(US_Workspace *parent):
        WContainerWidget(parent)
{
    _user = parent->user;
    //Set Style
    setStyleClass("overview");
    //Add the boxes for layout
    overhbox = new Wt::WHBoxLayout();
    this->setLayout(overhbox,0);

    Lvbox = new Wt::WVBoxLayout();
    overhbox->addLayout(Lvbox,0);

    Rcont= new WContainerWidget;
    overhbox->addWidget(Rcont);
    Rvbox = new Wt::WVBoxLayout();
    Rcont->setLayout(Rvbox,0);

    datehbox = new Wt::WHBoxLayout();
    Lvbox->addLayout(datehbox,0);


    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int currentDyear = now->tm_year+1900;
    int currentDmonth = now->tm_mon+1;
    int currentDday = now->tm_mday;
    int startDday=currentDday;
    int startDmonth=currentDmonth;
    int startDyear=currentDyear;
    if (startDmonth==1){
        startDyear=currentDyear-1;
        startDmonth=12;
    }
    else{
        startDmonth=currentDmonth-1;
    }

    //Add start date
    WDate olddate = WDate(startDyear,startDmonth,startDday);
    lblStartDate = new WLabel("Start Date:");
    StartDate = new WDateEdit();
    StartDate->setFormat("yyyy-MM-dd");
    StartDate->setDate(olddate);
    lblStartDate->setBuddy(StartDate);
    datehbox->addWidget(lblStartDate);
    datehbox->addWidget(StartDate);

    //Add end date
    EndDate = new WDateEdit();
    lblEndDate = new WLabel("End Date:");
    EndDate->setFormat("yyyy-MM-dd");
    EndDate->setDate(WDate::currentServerDate());
    lblEndDate->setBuddy(EndDate);
    datehbox->addWidget(lblEndDate);
    datehbox->addWidget(EndDate);

    //Add button
    btnSave = new WPushButton("Go");
    btnSave->clicked().connect(this, &US_OverviewGUI::btnSave_Click);
    datehbox->addWidget(btnSave);
    //Message if date is wrong
    lblMsg = new WLabel();
    Lvbox->addWidget(lblMsg);


    string stardate = StartDate->text().toUTF8();
    string endate = EndDate->text().toUTF8();
    vector<US_Transaction> Transactions=_user->getMain().getAllTransactions(stardate,endate);
    int s=Transactions.size();
    vector<string> typeexpenses= {};
    vector<double> valueexp={};
    model = new WStandardItemModel(this);
    //headers
    model->insertColumns(model->columnCount(), 2);

    model->setHeaderData(0, WString("Expense_Type"));
    model->setHeaderData(1, WString("Amount"));
    int rowData=0;

    for(int i=0; i<s; i++){
        string type=Transactions.at(i).getType();
        double val=Transactions.at(i).getValue();
        if (std::find(typeexpenses.begin(), typeexpenses.end(), type) != typeexpenses.end())
        {
            int pos = std::find(typeexpenses.begin(), typeexpenses.end(), type) - typeexpenses.begin();
            double sum=valueexp.at(pos);
            sum +=val;
            model->setData(pos, 1, sum);
        }
        else{
            typeexpenses.push_back(type);
            valueexp.push_back(val);
            model->setData(rowData, 0, WString(type));
            model->setData(rowData, 1, val);
            rowData++;
        }
    }

    //Add Bar chart
    barch = new Wt::Chart::WCartesianChart(this);
    barch->setModel(model);
    barch->setXSeriesColumn(0);
    Lvbox->addWidget(barch,1);
    for (int column = 1; column < model->columnCount(); ++column) {
        Wt::Chart::WDataSeries *series = new Wt::Chart::WDataSeries(column, Wt::Chart::BarSeries);
        barch->addSeries(series);
    }
    barch->resize(300, 200);

    //Add Pie chart
    piech = new Wt::Chart::WPieChart(this);
    piech->setModel(model);
    piech->setLabelsColumn(0);    // set the column that holds the labels
    piech->setDataColumn(1);      // set the column that holds the data
    piech->setDisplayLabels(Wt::Chart::Outside | Wt::Chart::TextLabel);
    piech->setStyleClass("overview-pie");
    piech->setPerspectiveEnabled(true, 0.2);
    piech->setShadowEnabled(true);
    piech->resize(600, 300);
    Rvbox->addWidget(piech);
    /*
    scatch = new Wt::Chart::WCartesianChart(this);
    scatch->setBackground(Wt::WColor(220, 220, 220));
    scatch->setModel(model);
    scatch->setXSeriesColumn(0);
    scatch->setType(Wt::Chart::ScatterPlot);
    scatch->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateScale);
    for (int column = 1; column < model->columnCount(); ++column) {
        Wt::Chart::WDataSeries *s = new Wt::Chart::WDataSeries(column, Wt::Chart::LineSeries);
        scatch->addSeries(s);
    }
    scatch->resize(500, 300);

    Rvbox->addWidget(scatch,1);*/
}

void US_OverviewGUI::btnSave_Click() {
    if(StartDate<EndDate){
        lblMsg->setText("End Date must be grater than start date");
        return;
    }
    string sdate = StartDate->text().toUTF8();
    string edate = EndDate->text().toUTF8();
}
