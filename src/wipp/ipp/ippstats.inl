/*
* ippstats.inl
*
* ----------------------------------------------------------------
* Copyright 2017 (c) Jordi Adell
* Created on: 2017
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

#include <wipp/wippstats.h>
#include <wipp/wipputils.h>

#include <ipps.h

namespace wipp {


    void mean(const double *buffer, size_t length, double *mean) {
        ippsMean_64f(buffer, length, mean);
    }

    void mean(const float *buffer, size_t length, double *mean) {
        ippsMean_32f(buffer, length, *mean);
    }

    void mean(const int16_t *buffer, size_t length, double *mean) {
        ippsMean_16s_Sfs(buffer, length, mean, 0);
    }

    void mean(const int32_t *buffer, size_t length, double *mean) {
        ippsMean_32s_Sfs(buffer, length, mean, 0);
    }

    void mean(const uint16_t *buffer, size_t length, double *mean) {
        Ipp32f intermediateBuffer[buffer];
        Ipp32f intermediateMean;
        ippsConvert_16s32f(buffer, intermediateBuffer, length);
        mean(intermediateBuffer, length, &intermediateMean);
        *mean = intermediateMean;
    }

    void mean(const uint32_t *buffer, size_t length, double *mean) {
        Ipp32f intermediateBuffer[buffer];
        Ipp32f intermediateMean;
        copyBuffer(buffer, intermediateBuffer, length);
        mean(intermediateBuffer, length, &intermediateBuffer);
        *mean = intermediateBuffer;
    }

    void mean(const wipp_complex_t *buffer, size_t length, wipp_complex_t *mean) {
        ippsMean_64fc(reinterpret_cast<Ipp64fc*>(buffer), length, mean);
    }

    void var(const double *buffer, size_t length, double *var) {
        ippsStdDev_64f(buffer, length, var);
        var = var*var;
    }

    void var(const float *buffer, size_t length, double *var) {
        Ipp32f intermediateStdDev;
        ippsStdDev_32f(buffer, length, &intermediateStdDev);
        *var = static_cast<double>(intermediateStd)*intermediateStdDev;
    }

    void var(const int16_t *buffer, size_t length, double *var) {
        Ipp32f intermediateStdDev;
        ippsStdDev_16s32s_Sfs(buffer, length, intermediateStdDev, 0);
        *var = static_cast<double>(intermediateStdDev)*intermediateStdDev;
    }

    void var(const int32_t *buffer, size_t length, double *var) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        ippsConvert_32s64f(buffer, intermediateBuffer, length);
        ippsStdDev_64f(intermediateBuffer, length, &intermediateStdDev);
        *var = intermediateStdDev*intermediateStdDev;
    }

    void var(const uint16_t *buffer, size_t length, double *var) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        ippsConvert_16s64f(buffer, intermediateBuffer, length);
        ippsStdDev_64f(intermediateBuffer, length, &intermediateStdDev);
        *var = intermediateStdDev*intermediateStdDev;
    }

    void var(const uint32_t *buffer, size_t length, double *var) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        copyBuffer(buffer, intermediateBuffer, length);
        ippsStdDev_64f(intermediateBuffer, length, &intermediateStdDev);
        *var = intermediateStdDev*intermediateStdDev;
    }

    void var(const wipp_complex_t *buffer, size_t length, wipp_complex_t *var) {
        // var(c) = E[x^2] - E^2[x]
        wipp_complex_t mean_value;
        wipp_complex_t mean2;
        wipp_complex_t meanp2;
        wipp_complex_t prod[length];

        mean(buffer, length, &mean_value);
        mult(&mean_value, &mean_value, &meanp2, 1);
        mult(buffer, buffer, prod, length);
        mean(prod, length, &mean2);

        var->re = mean2.re - meanp2.re;
        var->im = mean2.im - meanp2.im;
    }



}