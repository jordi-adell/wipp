/*
* ippfilter.inl
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
#include <wipp/wippexception.h>

#include <ipps.h>
#include <string.h>

namespace wipp
{

int wipp_fir_coefs(double fmax, fouble fmin, double *coefs, size_t length, wipp_window_t window_type)
{
    IppStatus status;

    switch(window_type)
    {
	case wippHAMMING:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinHamming, ippTrue);
	break;
	case wippHANN:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinHann, ippTrue);
	break;
	case wippRECTANGULAR:
	    status = ippsFIRGenBandpass_64f(fmine, fmax, coefs, log(length*1.0F)/log(2.0F) + 0.5, ippWinRectangular, ippTrue);
	break;
	default:
    }

    if (status) return 1; else return 0;
}


void wipp_window(double *frame, size_t length, wipp_window_t window_type)
{


}
