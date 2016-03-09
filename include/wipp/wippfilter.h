/*
 * wippfilter.h
 *
 * --------------------------------------------------------------------
 * Copyright 2016 (c) Jordi Adell
 * Created on: 2015
 * Author: Jordi Adell - adellj@gmail.com
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 */

#ifndef __FILTER_H_
#define __FILTER_H_

#include <wipp/wippdefs.h>

namespace wipp
{


// Definitions

struct wipp_fir_filter_t_;
typedef wipp_fir_filter_t_ wipp_fir_filter_t;

struct wipp_iir_filter_t_;
typedef wipp_iir_filter_t_ wipp_iir_filter_t;


typedef enum
{
    wippRECTANGULAR = 0,
    wippHAMMING,
    wippHANN,
} wipp_window_t;


// WINDOWING
void wipp_window(double *frame, size_t length, wipp_window_t window_type);

// FIR filters
int wipp_fir_coefs(double fmax, double fmin, double *coefs, size_t length, wipp_window_t window_type);
void wipp_init_fir(wipp_fir_filter_t *fir, double *coefs, size_t length);
void wipp_delete_fir(wipp_fir_filter_t *fir);
void wipp_fir_filter(wipp_fir_filter_t *fir, double *signal, size_t length);
void wipp_fir_filter(wipp_fir_filter_t *fir, const double *signal_in, double *singal_out, size_t length);

// IIR filter
void init_iir(wipp_iir_filter_t *iir, const double *a_coefs, size_t a_length, const double *b_coefs, size_t b_length);
void init_iir(wipp_iir_filter_t *iir,
	      const double *a_coefs, size_t a_length, const double *b_coefs, size_t b_length,
	      const double *x_pastValues, const double *y_pastValues);
void delete_iir(wipp_iir_filter_t *iir);
void iir_filter(wipp_iir_filter_t *iir, double *signal, size_t length);
void iir_filter(wipp_iir_filter_t *iir, const double *signal_in, double *signal_out, size_t length);



}

#endif // FILTER_H
