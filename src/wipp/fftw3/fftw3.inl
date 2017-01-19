/*
* fftw3.inl
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
#include <wipp/wippfft.h>
#include <fftw3.h>

#include <cstring>

namespace wipp
{

struct wipp_fft_t_
{
	fftw_plan forward_plan;
	double *forward_in;
	double *forward_out;

	fftw_plan backward_plan;
	double *backward_in;
	double *backward_out;

	size_t length;
};



void init_fft(wipp_fft_t **fft, size_t length)
{
    if(fft != NULL)
    {
	(*fft) = new wipp_fft_t_;
	(*fft)->length = length;
	(*fft)->forward_in  = fftw_alloc_real((*fft)->length);
	(*fft)->forward_out = fftw_alloc_real((*fft)->length);
	(*fft)->backward_in  = fftw_alloc_real((*fft)->length);
	(*fft)->backward_out = fftw_alloc_real((*fft)->length);
	(*fft)->forward_plan = fftw_plan_r2r_1d((*fft)->length, (*fft)->forward_in, (*fft)->forward_out, FFTW_R2HC, FFTW_ESTIMATE);
	(*fft)->backward_plan = fftw_plan_r2r_1d((*fft)->length, (*fft)->backward_in, (*fft)->backward_out, FFTW_HC2R, FFTW_ESTIMATE);
    }
}

void delete_fft(wipp_fft_t **fft)
{
    if (fft != NULL && *fft != NULL)
    {
	fftw_free((*fft)->forward_in);
	fftw_free((*fft)->forward_out);
	fftw_free((*fft)->backward_in);
	fftw_free((*fft)->backward_out);
	fftw_destroy_plan((*fft)->forward_plan);
	fftw_destroy_plan((*fft)->backward_plan);
	*fft = NULL;
    }
}

wipp_fft_t* fft(const double *signal, double *spectrum, wipp_fft_t* wipp_fft)
{
    memcpy(reinterpret_cast<void*>(wipp_fft->forward_in),
	   signal, sizeof(double)*wipp_fft->length);

    fftw_execute_r2r(wipp_fft->forward_plan,
			 wipp_fft->forward_in, wipp_fft->forward_out);

    wipp_complex_t *spectrum_c = reinterpret_cast<wipp_complex_t*>(spectrum);

    size_t i = 0;
    spectrum_c[i].re = wipp_fft->forward_out[i];
    spectrum_c[i].im = 0;
    for (i = 1; i < wipp_fft->length/2; ++i)
    {
	spectrum_c[i].re = wipp_fft->forward_out[i];
	spectrum_c[i].im = wipp_fft->forward_out[wipp_fft->length - i];
    }
    spectrum_c[i].re = wipp_fft->forward_out[i];
    spectrum_c[i].im = 0;
}

wipp_fft_t* ifft(const double *spectrum, double *signal, wipp_fft_t* wipp_fft)
{

    const wipp_complex_t *spectrum_c = reinterpret_cast<const wipp_complex_t*>(spectrum);

    size_t i = 0;
    wipp_fft->backward_in[i] = spectrum_c[i].re;
    for (i = 1; i < wipp_fft->length/2; ++i)
    {
	wipp_fft->backward_in[i] = spectrum_c[i].re;
	wipp_fft->backward_in[wipp_fft->length - i] = spectrum_c[i].im;
    }
    wipp_fft->backward_in[i] = spectrum_c[i].re;

    fftw_execute_r2r(wipp_fft->backward_plan,
		     wipp_fft->backward_in, wipp_fft->backward_out);
    memcpy(signal, reinterpret_cast<void*>(wipp_fft->backward_out), sizeof(double)*wipp_fft->length);
}

int get_fft_length(wipp_fft_t* wipp_fft)
{
    return wipp_fft->length;
}


}
