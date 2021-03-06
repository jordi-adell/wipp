/*
* wippstats.h
*
* ----------------------------------------------------------------
* Copyright 2016 (c) Jordi Adell
* Created on: 2015
* 	Author: Jordi Adell - adellj@gmail.com
* ----------------------------------------------------------------
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
* ----------------------------------------------------------------
*/

#ifndef __WIPPSTATS_H_
#define __WIPPSTATS_H_

#include <wipp/wippdefs.h>

namespace wipp
{

void median(const double *buffer, size_t length, double *median);
void median(const float *buffer, size_t length, float *median);
void median(const int16_t *buffer, size_t length, int16_t *median);
void median(const int32_t *buffer, size_t length, int32_t *median);
void median(const uint16_t *buffer, size_t length, uint16_t *median);
void median(const uint32_t *buffer, size_t length, uint32_t *median);


void mean(const double *buffer, size_t length, double *mean);
void mean(const float *buffer, size_t length, double *mean);
void mean(const int16_t *buffer, size_t length, double *mean);
void mean(const int32_t *buffer, size_t length, double *mean);
void mean(const uint16_t *buffer, size_t length, double *mean);
void mean(const uint32_t *buffer, size_t length, double *mean);
void mean(const wipp_complex_t *buffer, size_t length, wipp_complex_t *mean);


void var(const double *buffer, size_t length, double *var);
void var(const float *buffer, size_t length, double *var);
void var(const int16_t *buffer, size_t length, double *var);
void var(const int32_t *buffer, size_t length, double *var);
void var(const uint16_t *buffer, size_t length, double *var);
void var(const uint32_t *buffer, size_t length, double *var);
void var(const wipp_complex_t *buffer, size_t length, wipp_complex_t *var);


void stddev(const double *buffer, size_t length, double *stddev);
void stddev(const float *buffer, size_t length, double *stddev);
void stddev(const int16_t *buffer, size_t length, double *stddev);
void stddev(const int32_t *buffer, size_t length, double *stddev);
void stddev(const uint16_t *buffer, size_t length, double *stddev);
void stddev(const uint32_t *buffer, size_t length, double *stddev);


void sum(const double *buffer, size_t length, double *sum);
void sum(const float *buffer, size_t length, float *sum);
void sum(const int16_t *buffer, size_t length, int16_t*sum);
void sum(const int32_t *buffer, size_t length, int32_t *sum);
void sum(const uint16_t *buffer, size_t length, uint16_t *sum);
void sum(const uint32_t *buffer, size_t length, uint32_t *sum);
void sum(const wipp_complex_t *buffer, size_t length, wipp_complex_t *sum);


void min(const double *buffer, size_t length, double *min);
void min(const float *buffer, size_t length, float *min);
void min(const int16_t *buffer, size_t length, int16_t *min);
void min(const int32_t *buffer, size_t length, int32_t *min);
void min(const uint16_t *buffer, size_t length, uint16_t *min);
void min(const uint32_t *buffer, size_t length, uint32_t *min);
void min(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min);

void max(const double *buffer, size_t length, double *max);
void max(const float *buffer, size_t length, float *max);
void max(const int16_t *buffer, size_t length, int16_t *max);
void max(const int32_t *buffer, size_t length, int32_t *max);
void max(const uint16_t *buffer, size_t length, uint16_t *max);
void max(const uint32_t *buffer, size_t length, uint32_t *max);
void max(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max);

void maxAbs(const double *buffer, size_t length, double *max);
void maxAbs(const float *buffer, size_t length, float *max);
void maxAbs(const int16_t *buffer, size_t length, int16_t *max);
void maxAbs(const int32_t *buffer, size_t length, int32_t *max);
void maxAbs(const uint16_t *buffer, size_t length, uint16_t *max);
void maxAbs(const uint32_t *buffer, size_t length, uint32_t *max);

void minidx(const double *buffer, size_t length, double *min, size_t *idx);
void minidx(const float *buffer, size_t length, float *min, size_t *idx);
void minidx(const int16_t *buffer, size_t length, int16_t *min, size_t *idx);
void minidx(const int32_t *buffer, size_t length, int32_t *min, size_t *idx);
void minidx(const uint16_t *buffer, size_t length, uint16_t *min, size_t *idx);
void minidx(const uint32_t *buffer, size_t length, uint32_t *min, size_t *idx);
void minidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, size_t *idx);


void maxidx(const double *buffer, size_t length, double *max, size_t *idx);
void maxidx(const float *buffer, size_t length, float *max, size_t *idx);
void maxidx(const int16_t *buffer, size_t length, int16_t *max, size_t *idx);
void maxidx(const int32_t *buffer, size_t length, int32_t *max, size_t *idx);
void maxidx(const uint16_t *buffer, size_t length, uint16_t *max, size_t *idx);
void maxidx(const uint32_t *buffer, size_t length, uint32_t *max, size_t *idx);
void maxidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max, size_t *idx);


void minmax(const double *buffer, size_t length, double *min, double *max);
void minmax(const float *buffer, size_t length, float *min, float *max);
void minmax(const int16_t *buffer, size_t length, int16_t *min, int16_t *max);
void minmax(const int32_t *buffer, size_t length, int32_t *min, int32_t *max);
void minmax(const uint16_t *buffer, size_t length, uint16_t *min, uint16_t *max);
void minmax(const uint32_t *buffer, size_t length, uint32_t *min, uint32_t *max);
void minmax(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, wipp_complex_t *max);

struct wipp_rand_t_;
typedef wipp_rand_t_ wipp_rand_t;

void init_rand_gaussian(wipp_rand_t **rand, double mean, double stddev);
void init_rand_gaussian(wipp_rand_t **rand, float mean, float stddev);
void init_rand_gaussian(wipp_rand_t **rand, int mean, int stddev);
void delete_rand(wipp_rand_t **rand);
void rand(wipp_rand_t *rand, double *buffer, size_t length);
void rand(wipp_rand_t *rand, float *buffer, size_t length);
void rand(wipp_rand_t *rand, int *buffer, size_t length);

}


#endif // __WIPPSTATS_H_
