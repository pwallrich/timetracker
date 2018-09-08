//
//  TimeTracker.cpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include "TimeTracker.hpp"

void TimeTracker::startTimeTracker() {
    tracking = true;
    startTime = time(0);

    // convert now to string form
    char* dt = ctime(&startTime);
    std::cout << "The local date and time is: " << dt << std::endl;
}

int TimeTracker::stopTimeTracker() {
    tracking = false;
    stopTime = time(0);
    return 1;
}

double TimeTracker::timePassed() {
    return difftime(time(0), startTime);
}

bool TimeTracker::isTracking() {
    return tracking;
}
