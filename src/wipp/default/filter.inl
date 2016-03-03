#include <wipp/wippfilter.h>

#include <math.h>

namespace wipp
{


void wipp_hamming(double *frame, size_t length)
{
    static double alpha = 0.53836;
    static double beta  = 0.46164;

    for (size_t i  = 0; i < length; ++i)
    {
	frame[i] = alpha - beta*cos(2*M_PI*i/(length-1));
    }
}

void wipp_hann(double *frame, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
	frame[i] *= (1 - cos(2*M_PI*i/(length-1)))/2;
    }
}





void wipp_sinc(double fmax, double fmin, double *sinc, size_t length)
{
    for (size_t i = 0; i < length/2; ++i)
    {
	sinc[i] = (sin(2*(i - length/2)*fmax) - sin(2*(i - length/2)*fmin))/(i*M_PI);
    }
    sinc[length/2] = 1;
    for (size_t i = length/2 + 1; i < length; ++i)
    {
	sinc[i] = (sin(2*(i - length/2)*fmax) - sin(2*(i - length/2)*fmin))/(i*M_PI);
    }
}

void wipp_window(double *frame, size_t length, wipp_window_t window_type)
{
    switch(window_type)
    {
	case wippHANN:
	    wipp_hann(frame, length);
	break;
	case wippHAMMING:
	    wipp_hamming(frame, length);
	break;
	case wippRECTANGULAR:
	default:
	break;
    }
}

int wipp_fir_coefs(double fmax, double fmin, double *coefs, size_t length, wipp_window_t window_type)
{
    wipp_sinc(fmax, fmin, coefs, length);
    wipp_window(coefs, length, window_type);
    return 0;
}



}
