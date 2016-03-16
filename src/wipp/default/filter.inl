/*
* filter.inl
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
#include <wipp/wippfilter.h>

#include <cstring>
#include <math.h>

namespace wipp
{

template <typename T>
void wipp_hamming(T *frame, size_t length)
{
    static double alpha = 0.53836;
    static double beta  = 0.46164;

    for (size_t i  = 0; i < length; ++i)
    {
	frame[i] *= (alpha - beta*cos(2*M_PI*i/(length-1)));
    }
}

template<typename T>
void wipp_hann(T *frame, size_t length)
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



template<typename T>
void window_core(T *frame, size_t length, wipp_window_t window_type)
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

void window(double *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }
void window(float *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }
void window(int16_t *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }
void window(int32_t *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }
void window(uint16_t *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }
void window(uint32_t *frame, size_t length, wipp_window_t window_type) { window_core(frame, length, window_type); }






int fir_coefs(double fmax, double fmin, double *coefs, size_t length, wipp_window_t window_type)
{
    wipp_sinc(fmax, fmin, coefs, length);
    window(coefs, length, window_type);
    return 0;
}


struct wipp_fir_filter_t_ {
	double *buffer;
	size_t position;
	size_t order;
	double *coefs; // should it be const?
};

void init_fir(wipp_fir_filter_t *fir, const double *coefs, size_t length)
{
    fir = new wipp_fir_filter_t_();
    fir->order = length;
    fir->buffer = new double[fir->order];
    memset(fir->buffer,0,length*sizeof(double));
    fir->position = 0;
    fir->coefs = new double[fir->order];
    memcpy(fir->coefs, coefs, fir->order*sizeof(double));
}

void init_fir(wipp_fir_filter_t *fir, const double *coefs, size_t length, const double *pastValues)
{
    init_fir(fir, coefs, length);
    memcpy(fir->buffer, pastValues, length);
}


void delete_fir(wipp_fir_filter_t *fir)
{
    delete[] fir->buffer;
    delete[] fir->coefs;
    delete fir;
    fir = NULL;
}

void fir_filter(wipp_fir_filter_t *fir, double *signal, size_t length)
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

void fir_filter(wipp_fir_filter_t *fir, const double *signal_in, double *signal_out, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
	signal_out[i] = 0;
	for (size_t j = 0,k = fir->position; j < fir->order; ++j, k = (k+1)%fir->order)
	{
	    signal_out[i] = fir->buffer[k] * fir->coefs[j];
	}
	fir->buffer[fir->position] = signal_in[i];
	fir->position = (fir->position + 1) % fir->order;
    }
}

struct wipp_iir_filter_t_
{
	size_t a_order;
	size_t b_order;
	double *a_coefs;
	double *b_coefs;
	size_t x_position;
	size_t y_position;
	double *x_buffer;
	double *y_buffer;
};


void init_iir(wipp_iir_filter_t *iir, const double *a_coefs, size_t a_length, const double *b_coefs, size_t b_length)
{
    iir = new wipp_iir_filter_t();
    iir->a_order = a_length;
    iir->b_order = b_length;
    iir->a_coefs = new double[iir->a_order];
    iir->b_coefs = new double[iir->b_order];
    iir->x_position = 0;
    iir->y_position = 0;
    iir->x_buffer = new double[iir->b_order];
    iir->y_buffer = new double[iir->a_order];

    memcpy(iir->a_coefs, a_coefs, a_length*sizeof(double));
    memcpy(iir->b_coefs, b_coefs, b_length*sizeof(double));

}

void init_iir(wipp_iir_filter_t *iir,
	      const double *a_coefs, size_t a_length,
	      const double *b_coefs, size_t b_length,
	      const double *x_pastValues, const double *y_pastValues)
{
    init_iir(iir, a_coefs, a_length, b_coefs, b_length);
    memcpy(iir->x_buffer, x_pastValues, b_length*sizeof(double));
    memcpy(iir->y_buffer, y_pastValues, a_length*sizeof(double));
}


void delete_iir(wipp_iir_filter_t *iir)
{
    delete[] iir->x_buffer;
    delete[] iir->y_buffer;
    delete[] iir->a_coefs;
    delete[] iir->b_coefs;
    delete iir;
}

void iir_filter(wipp_iir_filter_t *iir, const double *signal_in, double *signal_out, size_t length)
{
    //
    //   y(n) = gain * (sum_i a_i*x(n-i) + sum_j b_j*x(n-j) )
    //

    for (size_t i = 0; i < length; ++i)
    {
	signal_out[i] = 0;
	//	for (size_t a = 0; a < iir->a_order; ++a)
	for (size_t a = 0,k = iir->y_position; a < iir->a_order; ++a, k = (k+1)%iir->a_order)
	{
	    signal_out[i] -= iir->a_coefs[a] * iir->y_buffer[k];
	}
	for (size_t b = 0,k = iir->x_position; b < iir->b_order; ++b, k = (k+1)%iir->b_order)
	{
	    signal_out[i] += iir->b_coefs[b] * iir->x_buffer[k];
	}

	iir->x_buffer[iir->x_position] = signal_in[i];
	iir->y_buffer[iir->y_position] = signal_out[i];

	iir->x_position = (iir->x_position + 1) % iir->b_order;
	iir->y_position = (iir->y_position + 1) % iir->a_order;

    }

}


void iir_filter(wipp_iir_filter_t *iir, double *signal, size_t length)
{
    double result;
    for (size_t i = 0; i < length; ++i)
    {
	result = 0;
	for (size_t a = 0,k = iir->y_position; a < iir->a_order; ++a, k = (k+1)%iir->a_order)
	{
	    result -= iir->a_coefs[a] * iir->y_buffer[k];
	}
	for (size_t b = 0,k = iir->x_position; b < iir->b_order; ++b, k = (k+1)%iir->b_order)
	{
	    result += iir->b_coefs[b] * iir->x_buffer[k];
	}

	iir->x_buffer[iir->x_position] = signal[i];
	iir->y_buffer[iir->y_position] = result;
	signal[i] = result;

	iir->x_position = (iir->x_position + 1) % iir->b_order;
	iir->y_position = (iir->y_position + 1) % iir->a_order;
    }
}

}
