//
//  wxmApp.cpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include "TimeTrackerApp.hpp"
#include "HomeView.hpp"


bool TimeTrackerApp::OnInit() {
    homeView = new HomeUI(NULL);
    homeView->Show(true);
    return true;
}

void TimeTrackerApp::toggleClicked() {
    printf("toggle clicked");
}

void TimeTrackerApp::exitClicked() {
    printf("exit clicked");
}

void TimeTrackerApp::openedList() {
    
}
