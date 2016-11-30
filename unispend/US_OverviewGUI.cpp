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

    Rvbox = new Wt::WVBoxLayout();
    overhbox->addLayout(Rvbox,0);

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
    vector<string> dates= {};
    dates.push_back(stardate);
    model = new WStandardItemModel(this);
    //headers
    model->insertColumns(model->columnCount(), 2);
    model->setHeaderData(0, WString("Expense_Type"));
    model->setHeaderData(1, WString("Amount"));
    int rowData=0;
    for(int i=0; i<s; i++){
        string type=Transactions.at(i).getType();
        double val=Transactions.at(i).getValue();
        string date=Transactions.at(i).getDate();
        if (std::find(dates.begin(), dates.end(), date) == dates.end()){
            dates.push_back(date);
        }
        if (std::find(typeexpenses.begin(), typeexpenses.end(), type) != typeexpenses.end())
        {
            int pos = std::find(typeexpenses.begin(), typeexpenses.end(), type) - typeexpenses.begin();
            double sum=valueexp.at(pos);
            sum +=val;
            valueexp.at(pos)=sum;
        }
        else{
            rowData++;
            typeexpenses.push_back(type);
            valueexp.push_back(val);
        }
    }
    if (std::find(dates.begin(), dates.end(), endate) == dates.end()){
        dates.push_back(endate);
    }
    //Add things to bar and pie chart model
    model->insertRows(model->rowCount(), rowData);
    for(int j=0; j<rowData; j++){
        model->setData(j, 0,WString(typeexpenses.at(j)));
        model->setData(j, 1, valueexp.at(j));
    }

    //Get model for Scatter chart
    std::sort(dates.begin(), dates.end());
    scatmodel = new WStandardItemModel(this);
    scatmodel->insertColumns(scatmodel->columnCount(), 2);
    scatmodel->setHeaderData(0, WString("Date"));
    scatmodel->setHeaderData(1, WString("Amount"));
    double totalspend=0;
    int siz=dates.size();
    for(int k=0; k<siz; k++){
        string curdate=dates.at(k);
        vector<US_Transaction> onedaytransactions=_user->getMain().getAllTransactions(curdate,curdate);
        int sizeofday=onedaytransactions.size();
        for(int l=0; l<sizeofday;l++){
            totalspend+=onedaytransactions.at(l).getValue();
        }

        cout<<"\n";
        cout<<curdate;
        cout<<"\n";
        cout<<totalspend;

        scatmodel->setData(k, 0,WString(curdate));
        scatmodel->setData(k, 1, totalspend);
    }

    //Add Bar chart
    barch = new Wt::Chart::WCartesianChart(this);
    barch->setModel(model);
    barch->setXSeriesColumn(0);
    Lvbox->addWidget(barch,1);
    series = new Wt::Chart::WDataSeries(1, Wt::Chart::BarSeries,Wt::Chart::Axis::Y1Axis);
    barch->addSeries(*series);
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
    
    scatch = new Wt::Chart::WCartesianChart(this);
    scatch->setBackground(Wt::WColor(220, 220, 220));
    scatch->setModel(scatmodel);
    scatch->setXSeriesColumn(0);
    scatch->setType(Wt::Chart::ScatterPlot);
    scatch->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateScale);
    scatseries = new Wt::Chart::WDataSeries(1, Wt::Chart::LineSeries,Wt::Chart::Axis::Y1Axis);
    scatch->addSeries(*scatseries);
    scatch->resize(500, 300);
    Rvbox->addWidget(scatch);
}

void US_OverviewGUI::btnSave_Click() {
    if(StartDate>EndDate){
        lblMsg->setText("End Date must be greater than start date");
        return;
    }
    string sdate = StartDate->text().toUTF8();
    string edate = EndDate->text().toUTF8();
}
