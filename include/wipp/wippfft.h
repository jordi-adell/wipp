/*
 * wippfft.h
 * 
 * ----------------------------------------------------------------------
 * Copyright 2016 (c) Jordi Adell
 * Created on: 2015
 * Author: Jordi Adell - adellj@gmail.com
 * ----------------------------------------------------------------------
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
 * ----------------------------------------------------------------------
 */

#ifndef __WIPP_FFT_H_
#define __WIPP_FFT_H_

#include <wipp/wippdefs.h>

namespace wipp
{

struct wipp_fft_t_;
typedef wipp_fft_t_ wipp_fft_t;

/**
 * @brief init_wipp_fft  constructs a wipp_fft structure
 * @param length  of the FFT and must be 128,256,512, ...
 * @return
 */
void init_wipp_fft(wipp_fft_t **fft, size_t length);

void delete_wipp_fft(wipp_fft_t **fft);

/**
 * @brief fft Calculates the Fast Fourier Transform of singal
 * and places the result in spectrum
 * @param signal  vector containing the signal to transform
 * @param signallength   length of the signal (must be equal to length in init_wipp_fft)
 * @param spectrum   vector with engough space to store the FFT
 * @param speclength  allocated space for vector spectrum (must be equal to length in init_wipp_fft)
 * @param wipp_fft   pointer to an initialise wipp_fft structure.
 * @return wipp_fft or null if something went wrong
 */
wipp_fft_t* fft(const double *signal, double *spectrum, wipp_fft_t* wipp_fft);
/**
 * @brief ifft  Does the inverse FFT
 * @return wipp_fft or null if something went wrong
 */
wipp_fft_t* ifft(const double *spectrum, double *signal, wipp_fft_t* wipp_fft);

int get_fft_length(wipp_fft_t* wipp_fft);
}

#endif
