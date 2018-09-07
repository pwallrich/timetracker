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
    auto frame = new HomeView();
    frame->Show(true);
    return true;
}
