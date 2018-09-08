///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  7 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>

#include "TimeTracker.hpp"
#include <string>


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class HomeUI
///////////////////////////////////////////////////////////////////////////////
class HomeUI : public wxFrame
{
	private:
        TimeTracker tracker;
        void onTimer(wxTimerEvent& event);
        char* formatSeconds(int seconds);

	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxStaticText* timeLabel;
		wxButton* toggleButton;
		wxPanel* m_panel2;
        wxGrid* grid;
        wxTimer* timer;

        void toggleClicked( wxCommandEvent& event );


	public:
		HomeUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 566,351 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~HomeUI();

};

