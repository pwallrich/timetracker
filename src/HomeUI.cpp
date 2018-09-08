///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  7 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "HomeUI.h"


#define ID_TIMER 100//irgendeine passende ID
///////////////////////////////////////////////////////////////////////////

HomeUI::HomeUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

    timeLabel = new wxStaticText( m_panel1, wxID_ANY, _T("00:00:00"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE );
    int w,h;
    timeLabel->GetSize(&w, &h);
    wxFont font = wxFont(w, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
    timeLabel->SetFont(font);
    
	timeLabel->Wrap( -1 );
	bSizer3->Add( timeLabel, 1, wxALL|wxEXPAND, 5 );

	toggleButton = new wxButton( m_panel1, wxID_ANY, wxT("start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( toggleButton, 1, wxALL|wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, wxT("TimeTracking"), false );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel2, wxT("History"), false );
    
    grid = new wxGrid(m_panel2, wxID_ANY, wxPoint(0,0), wxSize(400,300));
    grid->CreateGrid( 0, 0 );
    

	bSizer6->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	toggleButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HomeUI::toggleClicked ), NULL, this );

    tracker = TimeTracker();
    timer = new wxTimer(this, ID_TIMER);
}

HomeUI::~HomeUI()
{
	// Disconnect Events
	toggleButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( HomeUI::toggleClicked ), NULL, this );
}

void HomeUI::toggleClicked(wxCommandEvent &event) {
    if(tracker.isTracking()) {
        tracker.stopTimeTracker();
        timer->Stop();
        this->Disconnect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(HomeUI::onTimer), NULL, this);
        toggleButton->SetLabel(_T("start"));
    } else {
        this->Connect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(HomeUI::onTimer), NULL, this);
        timer->Start(1000);
        tracker.startTimeTracker();
        toggleButton->SetLabel(_T("stop"));
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

void HomeUI::onTimer(wxTimerEvent& event) {
    int seconds = int(tracker.timePassed());
    char* secondsString = formatSeconds(seconds);
    timeLabel->SetLabel(secondsString);
}
