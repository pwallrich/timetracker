//
//  wxmApp.cpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include "TimeTrackerApp.hpp"
#include "HomeView.hpp"
#include "HomeUI.h"


bool TimeTrackerApp::OnInit() {
    auto frame = new HomeUI(NULL);
    
    frame->Show(true);
    return true;
}
