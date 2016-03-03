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
