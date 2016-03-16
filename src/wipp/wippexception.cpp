/*
* wippexception.cpp
* Copyright 2016 (c) Jordi Adell
* Created on: 2015
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
#include <wipp/wipp.h>
#include <wipp/wippexception.h>
#include <wipp/wipplogger.h>

namespace wipp
{

  // Declarations
  /** Prints a warning/error depending on the status, with the corresponding IPP message **/
#ifndef IPP_FOUND
  long ippGetStatusString(long status) {return status;}
#endif


  // Implementations
    WIppException::WIppException(long status) : std::exception()
    {
      _status = status;
      printStatus(status);
    }


  void printStatus(long status)
  {
    if (status > 0)
      {
	WARN_STREAM("IPP: " << ippGetStatusString(status));
      }
    else if (status < 0)
      {
	ERROR_STREAM("IPP: " << ippGetStatusString(status));
      }
  }

  bool checkStatus(int istatus, bool throwException)
  {

#ifdef IPP_FOUND

    IppStatus status = static_cast<IppStatus>(istatus);
    std::string msg;
    bool ret = false;
    switch(status)
      {
      case ippStsOk:
	break;

      case ippStsWaterfall:
	msg = "IPP: ";
	msg += ippGetStatusString(status);
	WARN_STREAM_ONCE(msg);
	break;

      default:
	if (status > 0)
	  msg += "IPP WARNING: ";
	else
	  msg += "IPP ERROR: ";
	msg += ippGetStatusString(status);
	if (throwException)
	  {
	    ret = true;
	    throw(WIppException(status));
	  }
	else
	  {
	    qa::reportBug(msg);
	    ret = true;
	  }
	break;
      }

    return ret;
#else
    if (istatus == 0)
      {
	return false;
      }
    else
      {
	return true;
      }
#endif
  }

}
