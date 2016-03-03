#include <wipp/wippfilter.h>
#include <wipp/wippexception.h>

#include <ipps.h>
#include <string.h>

namespace wipp
{

int wipp_fir_coefs(double fmax, fouble fmin, double *coefs, size_t length, wipp_window_t window_type)
{
    IppStatus status;

    switch(window_type)
    {
	case wippHAMMING:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinHamming, ippTrue);
	break;
	case wippHANN:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinHann, ippTrue);
	break;
	case wippRECTANGULAR:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinRectangular, ippTrue);
	break;
	default:
    }

    if (status) return 1; else return 0;
}


void wipp_window(double *frame, size_t length, wipp_window_t window_type)
{


}
