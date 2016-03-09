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

void power_spectrum(const wipp_complex_t *spectrum, double *power, size_t length);
void magnitude(const wipp_complex_t* buffer, double *magnitude, size_t length);

void ramp(double *buffer, size_t length, double offset, double slope);
void triangle(double *buffer, size_t length);



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
