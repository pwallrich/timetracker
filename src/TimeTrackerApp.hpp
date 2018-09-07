//
//  wxmApp.hpp
//  timeTracker
//
//  Created by Philipp Wallrich on 07.09.18.
//  Copyright © 2018 Philipp Wallrich. All rights reserved.
//

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class TimeTrackerApp: public wxApp
{
public:
    virtual bool OnInit() override;
};
