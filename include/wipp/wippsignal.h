/*
 * wippsignal.h
 *
 * ---------------------------------------------------------------------
 * Copyright 2016 (c) Jordi Adell
 * Created on: 2015
 * Author: Jordi Adell - adellj@gmail.com
 * ---------------------------------------------------------------------
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
 * ---------------------------------------------------------------------
 */

#ifndef __WIPPSIGNAL_H_
#define __WIPPSIGNAL_H_

#include <wipp/wippdefs.h>
#include <math.h>

namespace wipp
{

void power(const wipp_complex_t *buffer, double *power, size_t length);
void power(const double *buffer, double *power, size_t length);
void power(double *buffer, size_t length);
void magnitude(const wipp_complex_t* buffer, double *magnitude, size_t length);
void magnitude(const wipp_complex_t* buffer, float *magnitude, size_t length);

void ramp(double *buffer, size_t length, double offset, double slope);
void ramp(float *buffer, size_t length, double offset, double slope);
void ramp(int *buffer, size_t length, double offset, double slope);
void ramp(uint16_t *buffer, size_t length, double offset, double slope);

void triangle(double *buffer, size_t length, int period, double phase, double asym=0, double offset = 0);
void triangle(double *buffer, size_t length);

void tone(double *buffer, size_t length, double magnitude, double frequency, double phase);
void tone(float *buffer, size_t length, double magnitude, double frequency, double phase);
void tone(int32_t *buffer, size_t length, double magnitude, double frequency, double phase);
void tone(int16_t *buffer, size_t length, double magnitude, double frequency, double phase);

void threshold_lt(double *buffer, size_t length, double threshold, double value);
void threshold_lt(float *buffer, size_t length, float threshold, float value);
void threshold_lt(int16_t *buffer, size_t length, int16_t threshold, int16_t value);
void threshold_lt(int32_t *buffer, size_t length, int32_t threshold, int32_t value);
void threshold_lt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value);
void threshold_lt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value);
void threshold_lt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value);
void threshold_lt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value);
void threshold_lt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value);
void threshold_lt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value);
void threshold_lt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value);
void threshold_lt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value);

void threshold_gt(double *buffer, size_t length, double threshold, double value);
void threshold_gt(float *buffer, size_t length, float threshold, float value);
void threshold_gt(int16_t *buffer, size_t length, int16_t threshold, int16_t value);
void threshold_gt(int32_t *buffer, size_t length, int32_t threshold, int32_t value);
void threshold_gt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value);
void threshold_gt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value);
void threshold_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value);
void threshold_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value);
void threshold_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value);
void threshold_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value);
void threshold_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value);
void threshold_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value);

void threshold_let(double *buffer, size_t length, double threshold, double value);
void threshold_let(float *buffer, size_t length, float threshold, float value);
void threshold_let(int16_t *buffer, size_t length, int16_t threshold, int16_t value);
void threshold_let(int32_t *buffer, size_t length, int32_t threshold, int32_t value);
void threshold_let(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value);
void threshold_let(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value);
void threshold_let(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value);
void threshold_let(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value);
void threshold_let(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value);
void threshold_let(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value);
void threshold_let(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value);
void threshold_let(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value);

void threshold_get(double *buffer, size_t length, double threshold, double value);
void threshold_get(float *buffer, size_t length, float threshold, float value);
void threshold_get(int16_t *buffer, size_t length, int16_t threshold, int16_t value);
void threshold_get(int32_t *buffer, size_t length, int32_t threshold, int32_t value);
void threshold_get(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value);
void threshold_get(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value);
void threshold_get(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value);
void threshold_get(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value);
void threshold_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value);
void threshold_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value);
void threshold_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value);
void threshold_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value);

void threshold_lt_gt(double *buffer, size_t length, double threshold_lt, double value_lt, double threshold_gt, double value_gt);
void threshold_lt_gt(float *buffer, size_t length, float threshold_lt, float value_lt, float threshold_gt, float value_gt);
void threshold_lt_gt(int16_t *buffer, size_t length, int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt);
void threshold_lt_gt(int32_t *buffer, size_t length, int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt);
void threshold_lt_gt(uint16_t *buffer, size_t length, uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt);
void threshold_lt_gt(uint32_t *buffer, size_t length, uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt);
void threshold_lt_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold_lt, double value_lt, double threshold_gt, double value_gt);
void threshold_lt_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold_lt, float value_lt, float threshold_gt, float value_gt);
void threshold_lt_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt);
void threshold_lt_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt);
void threshold_lt_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt);
void threshold_lt_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt);

void threshold_let_get(double *buffer, size_t length, double threshold_let, double value_let, double threshold_get, double value_get);
void threshold_let_get(float *buffer, size_t length, float threshold_let, float value_let, float threshold_get, float value_get);
void threshold_let_get(int16_t *buffer, size_t length, int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get);
void threshold_let_get(int32_t *buffer, size_t length, int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get);
void threshold_let_get(uint16_t *buffer, size_t length, uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get);
void threshold_let_get(uint32_t *buffer, size_t length, uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get);
void threshold_let_get(const double *buffer_in, double *buffer_out, size_t length, double threshold_let, double value_let, double threshold_get, double value_get);
void threshold_let_get(const float *buffer_in, float *buffer_out, size_t length, float threshold_let, float value_let, float threshold_get, float value_get);
void threshold_let_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get);
void threshold_let_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get);
void threshold_let_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get);
void threshold_let_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get);


void linear2mel(const double *linear, double *mel, size_t length);
void linear2mel(const double *linear, double *mel, size_t length, const double* mult, const double *div );
void linear2mel(const float *linear, float *mel, size_t length);
void linear2mel(const float *linear, float *mel, size_t length, const float* mult, const float *div );

void mel2linear(const double *linear, double *mel, size_t length);
void mel2linear(const double *linear, double *mel, size_t length, const double* mult, const double *div );
void mel2linear(const float *linear, float *mel, size_t length);
void mel2linear(const float *linear, float *mel, size_t length, const float* mult, const float *div );


void cross_corr(const double *buffer1, size_t length, double *buffer2, size_t length2, double *corr, size_t corr_length, int lowLag);
void cross_corr(const float *buffer1, size_t length, float *buffer2, size_t length2, float *corr, size_t corr_length, int lowLag);
void cross_corr(const int32_t *buffer1, size_t length, int32_t *buffer2, size_t length2, int32_t *corr, size_t corr_length, int lowLag);
void cross_corr(const int16_t *buffer1, size_t length, int16_t *buffer2, size_t length2, int16_t *corr, size_t corr_length, int lowLag);
void cross_corr(const uint16_t *buffer1, size_t length, uint16_t *buffer2, size_t length2, uint16_t *corr, size_t corr_length, int lowLag);

void median_filter(const double *inbuffer, double *outbuffer, size_t length, int maskSize);
void median_filter(const float *inbuffer, float *outbuffer, size_t length, int maskSize);
void median_filter(const int16_t *inbuffer, int16_t *outbuffer, size_t length, int maskSize);
void median_filter(const int32_t *inbuffer, int32_t *outbuffer, size_t length, int maskSize);
void median_filter(const uint16_t *inbuffer, uint16_t *outbuffer, size_t length, int maskSize);
void median_filter(const uint32_t *inbuffer, uint32_t *outbuffer, size_t length, int maskSize);

void median_filter(double *buffer, size_t length, int maskSize);
void median_filter(float *buffer, size_t length, int maskSize);
void median_filter(int16_t *buffer, size_t length, int maskSize);
void median_filter(int32_t *buffer, size_t length, int maskSize);
void median_filter(uint16_t *buffer, size_t length, int maskSize);
void median_filter(uint32_t *buffer, size_t length, int maskSize);


}



#endif // __WIPPSIGNAL_H_
