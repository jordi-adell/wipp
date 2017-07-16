/*
* ippexception.cpp
* Copyright 2017 (c) Jordi Adell
* Created on: 2017
* 	Author: Jordi Adell - adellj@gmail.com
*
* This file is part of WIPP
*
* WIPP is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WIPP is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with WIPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "IPPException.h"
#include <wipp/wipplogger.h>

namespace wipp {


    IPPException::IPPException(IppStatus status) :
    WIppException(ippGetStatusString(status)) {

    }

    IPPException::IPPException(const std::string &message) :
    WIppException(message) {

    }

    void reportWaterfallWarning(IppStatus status) {
        WARN_STREAM(std::string("IPP: ") + ippGetStatusString(status));
    }

    bool isOk(IppStatus status)
    {
        if (status != ippStsOk)
        {
            if (status == ippStsWaterfall)
                reportWaterfallWarning(status);
            else if (status > 0) {
                WARN_STREAM("IPP: " << ippGetStatusString(status));
            } else
                throw(IPPException(status));
        }
        return (status == ippStsOk);
    }



}