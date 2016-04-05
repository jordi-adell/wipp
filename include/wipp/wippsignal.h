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

void ramp(double *buffer, size_t length, double offset, double slope);
void triangle(double *buffer, size_t length);



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

struct wipp_circular_buffer_t_;
typedef wipp_circular_buffer_t_ wipp_circular_buffer_t;

void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, double   *init_values, size_t length);
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, float    *init_values, size_t length);
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int16_t  *init_values, size_t length);
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int32_t  *init_values, size_t length);
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint16_t *init_values, size_t length);
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint32_t *init_values, size_t length);

template<typename T>
void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size)
{ init_cirular_buffer(buffer, size, (T*) NULL, 0); }

void delete_circular_buffer(wipp_circular_buffer_t **buffer);

void cf_read(wipp_circular_buffer_t *cb, double   *buffer, size_t length, size_t *stored);
void cf_read(wipp_circular_buffer_t *cb, float    *buffer, size_t length, size_t *stored);
void cf_read(wipp_circular_buffer_t *cb, int16_t  *buffer, size_t length, size_t *stored);
void cf_read(wipp_circular_buffer_t *cb, int32_t  *buffer, size_t length, size_t *stored);
void cf_read(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored);
void cf_read(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored);

void cf_write(wipp_circular_buffer_t *cb, double   *buffer, size_t length, size_t *stored);
void cf_write(wipp_circular_buffer_t *cb, float    *buffer, size_t length, size_t *stored);
void cf_write(wipp_circular_buffer_t *cb, int16_t  *buffer, size_t length, size_t *stored);
void cf_write(wipp_circular_buffer_t *cb, int32_t  *buffer, size_t length, size_t *stored);
void cf_write(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored);
void cf_write(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored);

void cf_skip(wipp_circular_buffer_t *cb, size_t length, size_t *skipped);
void cf_size(wipp_circular_buffer_t *cb, size_t *size);
void cf_occupancy(wipp_circular_buffer_t *cb, size_t *occupancy);
void cf_free(wipp_circular_buffer_t *cb, size_t *free);


void linear2mel(const double *linear, double *mel, size_t length);
void linear2mel(const double *linear, double *mel, size_t length, const double* mult, const double *div );
void linear2mel(const float *linear, float *mel, size_t length);
void linear2mel(const float *linear, float *mel, size_t length, const float* mult, const float *div );

void mel2linear(const double *linear, double *mel, size_t length);
void mel2linear(const double *linear, double *mel, size_t length, const double* mult, const double *div );
void mel2linear(const float *linear, float *mel, size_t length);
void mel2linear(const float *linear, float *mel, size_t length, const float* mult, const float *div );

}



#endif // __WIPPSIGNAL_H_
