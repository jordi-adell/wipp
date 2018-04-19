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
#include <memory>

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




void wipp_sinc(double fmin, double fmax, double *sinc, size_t length)
{

    if (fmin <= 0) fmin = 1e-100;
    if (fmax > 0.5) fmax = 0.5;

    double low_pass_max[length];
    double low_pass_min[length];

    double sum_max=0;
    double sum_min=0;

    low_pass_max[0] = low_pass_min[0] = 0;
    low_pass_max[length/2] = low_pass_min[length/2] = 1;

    for (long i = 1; i < length; ++i)
    {
	if (i != length/2)
	    low_pass_max[i] = sin((i-static_cast<long>(length)/2)*2*M_PI*fmax)/(2*M_PI*fmax*(i-static_cast<long>(length)/2));
	sum_max += low_pass_max[i];
    }

    for (long i = 1; i < length; ++i)
    {
	if (i != length/2)
	    low_pass_min[i] = sin((i-static_cast<long>(length)/2)*2*M_PI*fmin)/(2*M_PI*fmin*(i-static_cast<long>(length)/2));
	sum_min += low_pass_min[i];
    }

    for (size_t i = 1; i < length; ++i)
    {
	    sinc[i] = low_pass_max[i]/sum_max - low_pass_min[i]/sum_min;
    }
}

void wipp_sinc2(double fmin, double fmax, double *sinc2, size_t length)
{
    if (fmin <= 0) fmin = 1e-100;
    if (fmax > 0.5) fmax = 0.5;

    double bw = (fmax - fmin)/4;
    fmax = fmax - bw;
    fmin = fmin + bw;


    double sum, sum_fmin, sum_fmax;
    sum = sum_fmin = sum_fmax = 0;

    double low_pass_min[length];
    double low_pass_max[length];
    double band_pass[length];

    for (long i = 0; i < length; ++i)
    {
	if (i == 0)
	{
	    band_pass[i] = low_pass_max[i] = low_pass_min[i] = 0;
	}
	else if(i == length/2)
	{
	    band_pass[i] = low_pass_max[i] = low_pass_min[i] = 1;
	}
	else
	{
	    if (bw > 0) band_pass[i]   =  sin((i-static_cast<long>(length)/2)*2*M_PI*bw  )/(2*M_PI*bw*  (i-static_cast<long>(length)/2));
	    if (fmin > 0) low_pass_min[i] = sin((i-static_cast<long>(length)/2)*2*M_PI*fmin)/(2*M_PI*fmin*(i-static_cast<long>(length)/2));
	    if (fmax > 0) low_pass_max[i] = sin((i-static_cast<long>(length)/2)*2*M_PI*fmax)/(2*M_PI*fmax*(i-static_cast<long>(length)/2));
	}
	sum_fmin += low_pass_min[i];
	sum_fmax += low_pass_max[i];
    }

    if (bw <= 0) memset(band_pass, 0, length*sizeof(double));
    if (fmin <= 0){ memset(low_pass_min, 0, length*sizeof(double)); sum_fmin = 1;}
    if (fmax <= 0){ memset(low_pass_min, 0 , sizeof(double)); sum_fmax = 1;}

    for (size_t i=0; i < length; ++i)
    {
	sinc2[i] = (low_pass_max[i]/sum_fmax - low_pass_min[i]/sum_fmin)*(band_pass[i]);
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


int fir_coefs(double fmin, double fmax, double *coefs, size_t length, wipp_window_t window_type, wipp_freq_shape_t freq_shape)
{
    int ret = 0;
    switch (freq_shape) {
	case wippfRECTANGULAR:
	    wipp_sinc(fmin, fmax, coefs, length);
	    window(coefs, length, window_type);
	break;
	case wippfTRIANGULAR:
	    wipp_sinc2(fmin, fmax, coefs, length);
	    window(coefs, length, window_type);
	break;
	default:
	    ret = -1;
	break;
    }
    return ret;
}

int fir_coefs(double fmin, double fmax, double *coefs, size_t length, wipp_window_t window_type)
{
    wipp_sinc(fmin, fmax, coefs, length);
    window(coefs, length, window_type);
    return 0;
}


struct wipp_fir_filter_t_ {
	double *buffer;
	size_t position;
	size_t order;
	double *coefs; // should it be const?
};

void init_fir(wipp_fir_filter_t **fir, const double *coefs, size_t length)
{
    if (fir != NULL)
    {
	*fir = new wipp_fir_filter_t_();
	(*fir)->order = length;
	(*fir)->buffer = new double[(*fir)->order];
	memset((*fir)->buffer,0,length*sizeof(*((*fir)->buffer)));
	(*fir)->position = 0;
	(*fir)->coefs = new double[(*fir)->order];
	memcpy((*fir)->coefs, coefs, (*fir)->order*sizeof((*(*fir)->coefs)));
    }
}

void init_fir(wipp_fir_filter_t **fir, const double *coefs, size_t length, const double *pastValues)
{
    init_fir(fir, coefs, length);
    if (fir != NULL && *fir != NULL && (*fir)->buffer != NULL)
	memcpy((*fir)->buffer, pastValues, length*sizeof(*((*fir)->buffer)));
}


void delete_fir(wipp_fir_filter_t **fir)
{
    if (fir != NULL && *fir != NULL)
    {
	delete[] (*fir)->buffer;
	delete[] (*fir)->coefs;
	delete *fir;
	*fir = NULL;
    }
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
	fir->position = (fir->position + 1) % fir->order;
	fir->buffer[fir->position] = signal_in[i];

	signal_out[i] = 0;
	for (size_t j = 0,k = fir->position; j < fir->order; ++j, --k)
	{
	    signal_out[i] += fir->buffer[k] * fir->coefs[j];
	    if (k <= 0) k = fir->order;
	}
    }
}



void fir_get_coefs(wipp_fir_filter_t *fir, double *coefs, size_t length)
{
    memcpy(coefs, fir->coefs, std::min(length, fir->order)*sizeof(*(fir->coefs)));
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


void init_iir(wipp_iir_filter_t **iir, const double *a_coefs, size_t a_length, const double *b_coefs, size_t b_length)
{
    *iir = new wipp_iir_filter_t_;

    (*iir)->a_order = a_length;
    (*iir)->b_order = b_length;
    (*iir)->a_coefs = new double[(*iir)->a_order];
    (*iir)->b_coefs = new double[(*iir)->b_order];
    (*iir)->x_position = 0;
    (*iir)->y_position = 0;
    (*iir)->x_buffer = new double[(*iir)->a_order];
    (*iir)->y_buffer = new double[(*iir)->b_order];

    memcpy((*iir)->a_coefs, a_coefs, a_length*sizeof(double));
    memcpy((*iir)->b_coefs, b_coefs, b_length*sizeof(double));

    memset((*iir)->x_buffer, 0, (*iir)->a_order*sizeof(double));
    memset((*iir)->y_buffer, 0, (*iir)->b_order*sizeof(double));
}

void init_iir(wipp_iir_filter_t **iir,
	      const double *a_coefs, size_t a_length,
	      const double *b_coefs, size_t b_length,
	      const double *x_pastValues, const double *y_pastValues)
{
    init_iir(iir, a_coefs, a_length, b_coefs, b_length);
    if (x_pastValues != NULL)
	memcpy((*iir)->x_buffer, x_pastValues, a_length*sizeof(double));
    if (y_pastValues != NULL)
	memcpy((*iir)->y_buffer, y_pastValues, b_length*sizeof(double));
}


void delete_iir(wipp_iir_filter_t **iir)
{
    if (iir != NULL && *iir != NULL)
    {
	delete[] (*iir)->x_buffer;
	delete[] (*iir)->y_buffer;
	delete[] (*iir)->a_coefs;
	delete[] (*iir)->b_coefs;
	delete (*iir);
	*iir = NULL;
    }
}

void iir_filter(wipp_iir_filter_t *iir, const double *signal_in, double *signal_out, size_t length)
{
    //
    //   y(n) = gain * (sum_i a_i*x(n-i) - sum_j b_j*y(n-j) )
    //

    for (size_t i = 0; i < length; ++i)
    {
	iir->x_position = (iir->x_position + 1) % iir->b_order;
	iir->x_buffer[iir->x_position] = signal_in[i];

	signal_out[i] = 0;

	for (size_t b = 1,k = iir->y_position; b < iir->b_order; ++b, --k)
	{
	    signal_out[i] -= iir->b_coefs[b] * iir->y_buffer[k];
	    if (k <= 0) k = iir->b_order;
	}
	for (size_t a = 0,k = iir->x_position; a < iir->a_order; ++a, --k)
	{
	    signal_out[i] += iir->a_coefs[a] * iir->x_buffer[k];
	    if (k <= 0) k = iir->a_order;
	}

	if (iir->b_order > 0)
	{
	    signal_out[i] /= iir->b_coefs[0];
	}

	iir->y_position = (iir->y_position + 1) % iir->a_order;
	iir->y_buffer[iir->y_position] = signal_out[i];

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
