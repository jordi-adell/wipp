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

typedef enum
{
    wippRECTANGULAR = 0,
    wippHAMMING,
    wippHANN,
} wipp_window_t;

void wipp_window(double *frame, size_t length, wipp_window_t window_type);
int wipp_fir_coefs(double fmax, double fmin, double *coefs, size_t length, wipp_window_t window_type);

}

#endif // FILTER_H
