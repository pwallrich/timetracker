///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  7 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "HomeUI.h"

enum {
    ID_notebook1 = wxID_HIGHEST + 1,
    ID_panel1,
    ID_timeLabel,
    ID_toggleButton,
    ID_panel2,
    ID_grid,
    ID_TIMER
};


///////////////////////////////////////////////////////////////////////////

HomeUI::HomeUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, ID_notebook1, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, ID_panel1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

    timeLabel = new wxStaticText( m_panel1, ID_timeLabel, _T("00:00:00"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE );
    int w,h;
    timeLabel->GetSize(&w, &h);
    wxFont font = wxFont(w, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
    timeLabel->SetFont(font);

	timeLabel->Wrap( -1 );
	bSizer3->Add( timeLabel, 1, wxALL|wxEXPAND, 5 );

	toggleButton = new wxButton( m_panel1, ID_toggleButton, wxT("start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( toggleButton, 1, wxALL|wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, wxT("TimeTracking"), false );
	m_panel2 = new wxPanel( m_notebook1, ID_panel2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel2, wxT("History"), false );
    
    grid = new wxGrid(m_panel2, ID_grid, wxPoint(0,0), size);
    grid->CreateGrid( 0, 2 );
    auto colSize = size.GetWidth() / 4 - 20;
    grid->SetColSize(0, colSize);
    grid->SetColSize(1, colSize * 3);
    grid->SetDefaultColSize(colSize);
    grid->SetColLabelValue(0, "Time");
    grid->SetColLabelValue(1, "Date");

	bSizer6->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &HomeUI::toggleClicked, this, ID_toggleButton);
    Bind(wxEVT_NOTEBOOK_PAGE_CHANGING, &HomeUI::tabChanging, this, ID_notebook1);

    tracker = TimeTracker();
    timer = new wxTimer(this, ID_TIMER);
    fileDir = wxStandardPaths::Get().GetExecutablePath();
    fileName = "history.csv";
}

HomeUI::~HomeUI()
{
	// Disconnect Events
}

void HomeUI::toggleClicked(wxCommandEvent &event) {
    if(tracker.isTracking()) {
        tracker.stopTimeTracker();
        timer->Stop();
        this->Disconnect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(HomeUI::onTimer), NULL, this);
        toggleButton->SetLabel(_T("start"));
        saveToFile();
    } else {
        this->Connect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(HomeUI::onTimer), NULL, this);
        timer->Start(1000);
        tracker.startTimeTracker();
        toggleButton->SetLabel(_T("stop"));
    }
}

void HomeUI::tabChanging(wxBookCtrlEvent &event) {
    if (event.GetSelection() == 1) {
        loadAndDisplayData();
    }
}

char* HomeUI::formatSeconds(int seconds) {
    int h = seconds / 3600;
    int remaining = seconds % 3600;
    int m = remaining / 60;
    int s = remaining % 60;
    size_t needed = snprintf(NULL, 0, "%d:%d:%d", h, m ,s) + 1;
    char  *buffer = (char*) malloc(needed);
    sprintf(buffer, "%02d:%02d:%02d", h, m ,s);
    return buffer;

}

void HomeUI::saveToFile() {
    double duration = tracker.getDuration();
    time_t start = tracker.getStart();
    char* s = parseEntryToString(duration, start);
    wxTextFile tfile;
    if(!(wxDirExists(fileDir))) {
        wxMkDir(fileDir, wxS_DIR_DEFAULT);
    }
    if (wxFileExists(fileDir + fileName)) {
        tfile.Open(fileDir + fileName);
    } else {
        tfile.Create(fileDir + fileName);
    }
    tfile.AddLine(s);
    tfile.Write();
    tfile.Close();
}

char* HomeUI::parseEntryToString(double duration, time_t start) {
    size_t needed = snprintf(NULL, 0, "%d;%ld", int(duration), start) + 1;
    char  *buffer = (char*) malloc(needed);
    sprintf(buffer, "%d;%ld", int(duration), start);
    return buffer;
}

void HomeUI::loadAndDisplayData() {
    wxTextFile tfile;
    if (wxFileExists(fileDir + fileName)) {
        tfile.Open(fileDir + fileName);
    }
    if(grid->GetNumberRows() > 0)
        grid->DeleteRows(0, grid->GetNumberRows());

    grid->AppendRows(tfile.GetLineCount());

    for(int i=0; i<tfile.GetLineCount(); i++) {

        wxString str = tfile.GetLine(i);
        wxStringTokenizer tokenizer(str, ";");

        grid->SetCellValue(i, 0, updateTimeLabel(tokenizer.GetNextToken()));
        grid->SetCellValue(i, 1, updateStartDate(tokenizer.GetNextToken()));

    }

}

void HomeUI::onTimer(wxTimerEvent& event) {
    int seconds = int(tracker.timePassed());
    char* secondsString = formatSeconds(seconds);
    timeLabel->SetLabel(secondsString);
}

// MARK: display update calculations


/// update Label containing Duration
wxString HomeUI::updateTimeLabel(wxString secondsToken) {
    wxString res = "";
    int duration = wxAtoi(secondsToken);
    // calculate hours, minuntes, seconds from input secondsTokenn

    for ( int i = 3600; i >=60; i /= 60) {
        res += wxString::Format(wxT("%02d:"), duration / i);
        duration %=  i;
    }
    res += wxString::Format(wxT("%02d"), duration);

    return res;
}


wxString getWeekday(tm* startDate) {
    int weekday = startDate->tm_wday;
    wxString res;
    switch (weekday) {
        case 0:
            res = "Sonntag";
            break;
        case 1:
            res = "Montag";
            break;
        case 2:
            res = "Dienstag";
            break;
        case 3:
            res = "Mittwoch";
            break;
        case 4:
            res = "Donnerstag";
            break;
        case 5:
            res = "Freitag";
            break;
        case 6:
            res = "Samstag";
            break;
        default:
            res = "Error!";
            break;
    }

    return res;
}

wxString getMonth(tm* startDate) {
    int month = startDate->tm_mon;
    wxString res;
    switch (month) {
        case 0:
            res = "Januar";
            break;
        case 1:
            res = "Februar";
            break;
        case 2:
            res = "März";
            break;
        case 3:
            res = "April";
            break;
        case 4:
            res = "Mai";
            break;
        case 5:
            res = "Juni";
            break;
        case 6:
            res = "Juli";
            break;
        case 7:
            res = "August";
            break;
        case 8:
            res = "September";
            break;
        case 9:
            res = "Oktober";
            break;
        case 10:
            res = "November";
            break;
        case 11:
            res = "Dezember";
            break;
        default:
            res = "Error!";
            break;
    }

    return res;
}
/// update Label containing start Date
wxString HomeUI::updateStartDate(wxString dateInSecondsSinceEpoch) {
    long epoch = wxAtol(dateInSecondsSinceEpoch);
    // get time from epoch
    tm* startDate = localtime(&epoch);
    wxString weekday = getWeekday(startDate);
    wxString month = getMonth(startDate);
    // Montag 01 August 2018 19:51:01
    return wxString::Format(wxT("%s %02d %s %02d %02d:%02d:%02d"), weekday, startDate->tm_mday, month, startDate->tm_year + 1900, startDate->tm_hour, startDate->tm_min, startDate->tm_sec);
}



