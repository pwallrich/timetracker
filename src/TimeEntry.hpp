//
//  TimeEntry.hpp
//  TimeTracker
//
//  Created by Philipp Wallrich on 08.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#ifndef TimeEntry_hpp
#define TimeEntry_hpp

#include <stdio.h>
#include <ctime>
#include <string>

#endif /* TimeEntry_hpp */

struct TimeEntry {
    time_t starTime;
    time_t endTime;
    double duration;
    
    std::string description;
};
