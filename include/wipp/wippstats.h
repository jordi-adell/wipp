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

void mean(const double *buffer, size_t length, double *mean);
void mean(const float *buffer, size_t length, double *mean);
void mean(const int16_t *buffer, size_t length, double *mean);
void mean(const int32_t *buffer, size_t length, double *mean);
void mean(const uint16_t *buffer, size_t length, double *mean);
void mean(const uint32_t *buffer, size_t length, double *mean);

void sum(const double *buffer, size_t length, double *mean);
void sum(const float *buffer, size_t length, double *mean);
void sum(const int16_t *buffer, size_t length, double *mean);
void sum(const int32_t *buffer, size_t length, double *mean);
void sum(const uint16_t *buffer, size_t length, double *mean);
void sum(const uint32_t *buffer, size_t length, double *mean);



}


#endif // __WIPPSTATS_H_
