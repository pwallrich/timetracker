//
//  wxmView.hpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include <wx/wx.h>


class HomeView : public wxFrame {
public:
    HomeView();
    virtual ~HomeView();
protected:
    
private:
    wxTextCtrl *textControl;
    wxMenu *fileMenu;
    wxString currentDocPath;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void setupMenu();
    void bindMenu();
    void setupStatusBar();

    void NewFile(wxCommandEvent& event);
    void OpenFile(wxCommandEvent& event);
    void SaveFile(wxCommandEvent& event);
    void SaveFileAs(wxCommandEvent& event);
    void CloseFile(wxCommandEvent& event);
};
