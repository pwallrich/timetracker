//
//  TimeTracker.hpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#ifndef TimeTracker_hpp
#define TimeTracker_hpp

#include <stdio.h>
#include <ctime>
#include <iostream>
#endif /* TimeTracker_hpp */

class TimeTracker
{
public:
    void startTimeTracker();
    int stopTimeTracker();
    bool isTracking();
private:
    time_t startTime;
    time_t stopTime;
    bool tracking;
};
