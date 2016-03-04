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


struct wipp_fir_filter_t_ {
	double *buffer;
	size_t occupancy;
	size_t position;
	size_t order;
	double *coefs; // should it be const?
};

void wipp_init_fir(wipp_fir_filter_t *fir, const double *coefs, size_t length)
{
    fir = new wipp_fir_filter_t_();
    fir->order = length;
    fir->buffer = new double[fir->order];
    memset(fir->buffer,0,length*sizeof(double));
    fir->occupancy = fir->position = 0;
    fir->coefs = new double[fir->order];
    memcpy(fir->coefs, coefs, fir->order*sizeof(double));
}

void wipp_delete_fir(wipp_fir_filter_t *fir)
{
    delete[] fir->buffer;
    delete[] fir->coefs;
    delete fir;
    fir = NULL;
}

void wipp_fir_filter(wipp_fir_filter_t *fir, double *signal, size_t length)
{
    double result;
    for (size_t i = 0; i < length; ++i)
    {
	result = 0;
	for (size_t j = 0,k = fir->position; j < fir->order; ++j, k = (k+1)%fir->order)
	{
	    result += fir->buffer[k] * fir->coefs[j];
	}
	fir->buffer[fir->position] = signal[i];
	signal[i] = result;
	fir->position = (fir->position + 1) % fir->order;
    }
}

void wipp_fir_filter(wipp_fir_filter_t *fir, const double *signal_in, double *signal_out, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
	signal_out[i] = 0;
	for (size_t j = 0,k = fir->position; j < fir->order; ++j, k = (k+1)%fir->order)
	{
	    signal_out[i] = fir->buffer[k] * fir->coefs[j];
	}
	fir->buffer[fir->position] = signal_in[0];
	fir->position = (fir->position + 1) % fir->order;
    }
}


}
