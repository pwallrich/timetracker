//
//  wxmView.cpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include "HomeView.hpp"

#include <wx/grid.h>
#include <wx/clipbrd.h>
#include <wx/url.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/combo.h>
#include <wx/odcombo.h>
#include <wx/valgen.h>

#include "base.h"

#define frameWidth 800
#define frameHeight 600

enum
{
    TEXT_textControl = wxID_HIGHEST + 1,
    MENU_New,
    MENU_Open,
    MENU_Close,
    MENU_Save,
    MENU_SaveAs,
    MENU_Quit
};


HomeView::HomeView()
: wxFrame(NULL, wxID_ANY, "timeTracker")
{
    setupMenu();
    bindMenu();
    setupStatusBar();

    textControl = new wxTextCtrl(this, TEXT_textControl, _T("Hello"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
}

HomeView::~HomeView() {}

// ----------------------
// event handlers

void HomeView::OnExit(wxCommandEvent &event) {
    Close(true);
}

void HomeView::OnAbout(wxCommandEvent &event) {
    wxMessageBox("Build by Philipp Wallrich\nhttps://github.com/pwallrich", "TimeTracking Tool", wxOK | wxICON_INFORMATION);
}

void HomeView::NewFile(wxCommandEvent &event) {
    SetTitle(wxString(""));
    textControl->Clear();
    currentDocPath = "";
}

void HomeView::OpenFile(wxCommandEvent &event) {
    wxFileDialog* openDialog = new wxFileDialog(
        this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
        _("Text files (*.txt)|*.txt|C++ Source Files (*cpp, *cxx)|*.cpp;*.cxx|C Source Files (*.c)|*.c|C Header files (*.h)|*.h),"),
        wxFD_OPEN, wxDefaultPosition);

    // Creates a open file dialog with 4 file types
    if (openDialog->ShowModal() == wxID_OK) {
        currentDocPath = openDialog->GetPath();
        textControl->LoadFile(currentDocPath);
        SetTitle(wxString("Edit - ") << openDialog->GetFilename());
    }

    openDialog->Destroy();
}

void HomeView::CloseFile(wxCommandEvent &event) {
    SetTitle(wxString(""));
    textControl->Clear();
    currentDocPath = "";
}

void HomeView::SaveFile(wxCommandEvent &event) {
    textControl->SaveFile(currentDocPath);
}
void HomeView::SaveFileAs(wxCommandEvent &event) {
    
}

void HomeView::setupMenu() {
    fileMenu = new wxMenu();

    fileMenu->Append(MENU_New, wxT("&New...\tCtrl-N"),
                     wxT("Create a new file"));
    fileMenu->Append(MENU_Open, wxT("&Open...\tCtrl-O"),
                     wxT("Open an existing file"));
    fileMenu->Append(MENU_Close, wxT("&Close...\tCtrl-W"),
                     wxT("Close the current document"));
    fileMenu->Append(MENU_Save, wxT("&Save...\tCtrl-S"),
                     wxT("Save the current document"));
    fileMenu->Append(MENU_SaveAs, wxT("Save &As"),
                     wxT("Save the current document under a new file name"));
    fileMenu->Append(MENU_Quit, wxT("&Quit...\tCtrl-Q"),
                     wxT("Quit the editor"));
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
}

void HomeView::bindMenu() {
    Bind(wxEVT_MENU, &HomeView::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &HomeView::OnExit, this, wxID_EXIT);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::NewFile, this, MENU_New);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::OpenFile, this, MENU_Open);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::CloseFile, this, MENU_Close);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::SaveFile, this, MENU_Save);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::SaveFileAs, this, MENU_SaveAs);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &HomeView::OnExit, this, MENU_Quit);
}

void HomeView::setupStatusBar() {
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
    this->SetSize(frameWidth, frameHeight);
}
