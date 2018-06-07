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
#include <wipp/wippexception.h>

#include <ippcore.h>
#include <ipps.h>
#include <ippi.h>

#include <algorithm>

#define IPP64fc(x) reinterpret_cast<Ipp64fc*>(x)
#define cIPP64fc(x) reinterpret_cast<const Ipp64fc*>(x)

namespace wipp {


    template<typename T>
    void sort(const T *buffer, T *sorted, size_t length)
    {
        memcpy(sorted, buffer, sizeof(T)*length);
        std::sort(sorted, &sorted[length]);
    }


    template<typename T>
    void median_core(const T *buffer, size_t length, T* median)
    {
        T sorted[length];
        int center = static_cast<double>(length)/2 - 0.5;
        sort(buffer, sorted, length);
        *median = sorted[center];
    }

    void median(const double *buffer, size_t length, double *median){ median_core(buffer, length, median); }
    void median(const float *buffer, size_t length, float *median){ median_core(buffer, length, median); }
    void median(const int16_t *buffer, size_t length, int16_t *median){ median_core(buffer, length, median); }
    void median(const int32_t *buffer, size_t length, int32_t *median){ median_core(buffer, length, median); }
    void median(const uint16_t *buffer, size_t length, uint16_t *median){ median_core(buffer, length, median); }
    void median(const uint32_t *buffer, size_t length, uint32_t *median){ median_core(buffer, length, median); }

    void mean(const double *buffer, size_t length, double *mean) {
        ippsMean_64f(buffer, length, mean);
    }

    void mean(const float *buffer, size_t length, double *mean) {
        Ipp32f float_mean;
        ippsMean_32f(buffer, length, &float_mean, ippAlgHintFast);
        *mean = float_mean;
    }

    void mean(const int16_t *buffer, size_t length, double *mean) {
        Ipp16s integer_mean;
        ippsMean_16s_Sfs(buffer, length, &integer_mean, 0);
        *mean = integer_mean;
    }

    void mean(const int32_t *buffer, size_t length, double *mean) {
        Ipp32s integer_mean;
        ippsMean_32s_Sfs(buffer, length, &integer_mean, 0);
        *mean = integer_mean;
    }

    void mean(const uint16_t *buffer, size_t length, double *mean_value) {
        Ipp32f intermediateBuffer[length];
        ippsConvert_16u32f(buffer, intermediateBuffer, length);
        mean(intermediateBuffer, length, mean_value);
    }

    void mean(const uint32_t *buffer, size_t length, double *mean_value) {
        Ipp32f intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = buffer[i];
        mean(intermediateBuffer, length, mean_value);
    }

    void mean(const wipp_complex_t *buffer, size_t length, wipp_complex_t *mean) {
        ippsMean_64fc(reinterpret_cast<const Ipp64fc*>(buffer), length, reinterpret_cast<Ipp64fc*>(mean));
    }

    void var(const double *buffer, size_t length, double *var) {
        double standard_deviation;
        ippsStdDev_64f(buffer, length, &standard_deviation);
        *var = standard_deviation*standard_deviation;
    }

    void var(const float *buffer, size_t length, double *var) {
        Ipp32f intermediateStdDev;
        ippsStdDev_32f(buffer, length, &intermediateStdDev, ippAlgHintFast);
        *var = static_cast<double>(intermediateStdDev)*intermediateStdDev;
    }

    void var(const int16_t *buffer, size_t length, double *var) {
        Ipp32s intermediateStdDev;
        ippsStdDev_16s32s_Sfs(buffer, length, &intermediateStdDev, 0);
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
        Ipp32f intermediateBuffer[length];
        Ipp32f intermediateStdDev;
        ippsConvert_16u32f(buffer, intermediateBuffer, length);
        ippsStdDev_32f(intermediateBuffer, length, &intermediateStdDev, ippAlgHintFast);
        *var = intermediateStdDev*intermediateStdDev;
    }

    void var(const uint32_t *buffer, size_t length, double *var) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = buffer[i];
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

    void stddev(const double *buffer, size_t length, double *stddev) {
        ippsStdDev_64f(buffer, length, stddev);
    }

    void stddev(const float *buffer, size_t length, double *stddev) {
        Ipp32f float_stddev;
        ippsStdDev_32f(buffer, length, &float_stddev, ippAlgHintFast);
        *stddev = float_stddev;
    }

    void stddev(const int16_t *buffer, size_t length, double *stddev) {
        Ipp16s integer_stddev;
        ippsStdDev_16s_Sfs(buffer, length, &integer_stddev, ippAlgHintFast);
        *stddev = integer_stddev;
    }

    void stddev(const int32_t *buffer, size_t length, double *stddev) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        ippsConvert_32s64f(buffer, intermediateBuffer, length);
        ippsStdDev_64f(intermediateBuffer, length, &intermediateStdDev);
        *stddev = intermediateStdDev;
    }

    void stddev(const uint16_t *buffer, size_t length, double *stddev) {
        Ipp32f intermediateBuffer[length];
        Ipp32f intermediateStdDev;
        ippsConvert_16u32f(buffer, intermediateBuffer, length);
        ippsStdDev_32f(intermediateBuffer, length, &intermediateStdDev, ippAlgHintFast);
        *stddev = intermediateStdDev;
    }

    void stddev(const uint32_t *buffer, size_t length, double *stddev) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateStdDev;
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = buffer[i];
        ippsStdDev_64f(intermediateBuffer, length, &intermediateStdDev);
        *stddev = intermediateStdDev;
    }


    void sum(const double *buffer, size_t length, double *sum) {
        ippsSum_64f(buffer, length, sum);
    }

    void sum(const float *buffer, size_t length, float *sum) {
        ippsSum_32f(buffer, length, sum, ippAlgHintFast);
    }

    void sum(const int16_t *buffer, size_t length, int16_t*sum) {
        ippsSum_16s_Sfs(buffer, length, sum, 0);
    }

    void sum(const int32_t *buffer, size_t length, int32_t *sum) {
        ippsSum_32s_Sfs(buffer, length, sum, 0);
    }

    void sum(const uint16_t *buffer, size_t length, uint16_t *sum) {
        *sum = 0;
        for (size_t i = 0; i < length; ++i)
            *sum  += buffer[i];
    }

    void sum(const uint32_t *buffer, size_t length, uint32_t *sum) {
        *sum = 0;
        for (size_t i = 0; i < length; ++i)
            *sum += buffer[i];
    }

    void sum(const wipp_complex_t *buffer, size_t length, wipp_complex_t *sum) {
        ippsSum_64fc(cIPP64fc(buffer), length, IPP64fc(sum));
    }


    void min(const double *buffer, size_t length, double *min) {
        ippsMin_64f(buffer, length, min);
    }

    void min(const float *buffer, size_t length, float *min) {
        ippsMin_32f(buffer, length, min);
    }

    void min(const int16_t *buffer, size_t length, int16_t *min) {
        ippsMin_16s(buffer, length, min);
    }

    void min(const int32_t *buffer, size_t length, int32_t *min) {
        ippsMin_32s(buffer, length, min);
    }

    void min(const uint16_t *buffer, size_t length, uint16_t *min) {
        Ipp32f intermediateBuffer[length];
        Ipp32f intermediateMin;
        ippsConvert_16u32f(buffer, intermediateBuffer, length);
        ippsMin_32f(intermediateBuffer, length, &intermediateMin);
        *min = intermediateMin;
    }

    void min(const uint32_t *buffer, size_t length, uint32_t *min) {
        Ipp64f intermediateBuffer[length];
        Ipp64f intermediateMin;
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = buffer[i];
        ippsMin_64f(intermediateBuffer, length, &intermediateMin);
        *min = intermediateMin;
    }

    void min(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min) {
        Ipp64f magnitude[length];
        Ipp64f minimum_value;
        int minimum_index;
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), magnitude, length);
        ippsMinIndx_64f(magnitude, length, &minimum_value, &minimum_index);
        *min = buffer[minimum_index];
    }

    void max(const double *buffer, size_t length, double *max) {
        ippsMax_64f(buffer, length, max);
    }

    void max(const float *buffer, size_t length, float *max) {
        ippsMax_32f(buffer, length, max);
    }

    void max(const int16_t *buffer, size_t length, int16_t *max) {
        ippsMax_16s(buffer, length, max);
    }

    void max(const int32_t *buffer, size_t length, int32_t *max) {
        ippsMax_32s(buffer, length, max);
    }

    void max(const uint16_t *buffer, size_t length, uint16_t *max) {
        Ipp16u min;
        ippsMinMax_16u(buffer, length, &min, max);
    }

    void max(const uint32_t *buffer, size_t length, uint32_t *max) {
        Ipp32u min;
        ippsMinMax_32u(buffer, length, &min, max);
    }

    void max(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max) {
        Ipp64f magnitude[length];
        Ipp64f maximum_value;
        int maximum_index;
        ippsMax_64f(magnitude, length, &maximum_value);
        *max = buffer[maximum_index];
    }

    void maxAbs(const double *buffer, size_t length, double *max) {
        ippsMaxAbs_64f(buffer, length, max);
    }

    void maxAbs(const float *buffer, size_t length, float *max) {
        ippsMaxAbs_32f(buffer, length, max);
    }

    void maxAbs(const int16_t *buffer, size_t length, int16_t *max) {
        ippsMaxAbs_16s(buffer, length, max);
    }

    void maxAbs(const int32_t *buffer, size_t length, int32_t *max) {
        ippsMaxAbs_32s(buffer, length, max);
    }

    void maxAbs(const uint16_t *buffer, size_t length, uint16_t *max_value) {
        max(buffer, length, max_value);
    }

    void maxAbs(const uint32_t *buffer, size_t length, uint32_t *max_value) {
        max(buffer, length, max_value);
    }

    void minidx(const double *buffer, size_t length, double *min, size_t *idx) {
        int index;
        ippsMinIndx_64f(buffer, length, min, &index);
        *idx = index;
    }

    void minidx(const float *buffer, size_t length, float *min, size_t *idx) {
        int index;
        ippsMinIndx_32f(buffer, length, min, &index);
        *idx = index;
    }

    void minidx(const int16_t *buffer, size_t length, int16_t *min, size_t *idx) {
        int index;
        ippsMinIndx_16s(buffer, length, min, &index);
        *idx = index;
    }

    void minidx(const int32_t *buffer, size_t length, int32_t *min, size_t *idx) {
        int index;
        ippsMinIndx_32s(buffer, length, min, &index);
        *idx = index;
    }

    void minidx(const uint16_t *buffer, size_t length, uint16_t *min, size_t *idx) {
        int min_index, max_index;
        Ipp16u max;
        ippsMinMaxIndx_16u(buffer, length, min, &min_index, &max, &max_index);
        *idx = min_index;
    }

    void minidx(const uint32_t *buffer, size_t length, uint32_t *min, size_t *idx){
        Ipp32u max;
        int minimum_index, maximum_index;
        ippsMinMaxIndx_32u(buffer, length, min, &minimum_index, &max, &maximum_index);
        *idx = minimum_index;
    }

    void minidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, size_t *idx) {
        Ipp64f magnitud[length], minimum_value;
        int index;
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), magnitud, length);
        ippsMinIndx_64f(magnitud,length, &minimum_value, &index);
        *idx = index;
        *min = buffer[index];
    }

    void maxidx(const double *buffer, size_t length, double *max, size_t *idx) {
        int index;
        ippsMaxIndx_64f(buffer, length, max, &index);
        *idx = index;
    }

    void maxidx(const float *buffer, size_t length, float *max, size_t *idx) {
        int index;
        ippsMaxIndx_32f(buffer, length, max, &index);
        *idx = index;
    }

    void maxidx(const int16_t *buffer, size_t length, int16_t *max, size_t *idx) {
        int index;
        ippsMaxIndx_16s(buffer, length, max, &index);
        *idx = index;
    }

    void maxidx(const int32_t *buffer, size_t length, int32_t *max, size_t *idx) {
        int index;
        ippsMaxIndx_32s(buffer, length, max, &index);
        *idx = index;
    }

    void maxidx(const uint16_t *buffer, size_t length, uint16_t *max, size_t *idx) {
        int index;
        Ipp16u minimum_value;
        int minimum_index, maximum_index;
        ippsMinMaxIndx_16u(buffer, length, &minimum_value, &minimum_index, max, &maximum_index);
        *idx = maximum_index;
    }

    void maxidx(const uint32_t *buffer, size_t length, uint32_t *max, size_t *idx) {
        int index;
        Ipp32u minimum_value;
        int minimum_index, maximum_index;
        ippsMinMaxIndx_32u(buffer, length, &minimum_value, &minimum_index, max, &maximum_index);
        *idx = maximum_index;
    }

    void maxidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max, size_t *idx) {
        Ipp64f magnitude[length];
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), magnitude, length);
        Ipp64f magnitude_max;
        int index;
        ippsMaxIndx_64f(magnitude, length, &magnitude_max, &index);
        *max = buffer[index];
        *idx = index;
    }


    void minmax(const double *buffer, size_t length, double *min, double *max) {
        ippsMinMax_64f(buffer, length, min, max);
    }

    void minmax(const float *buffer, size_t length, float *min, float *max) {
        ippsMinMax_32f(buffer, length, min, max);
    }

    void minmax(const int16_t *buffer, size_t length, int16_t *min, int16_t *max){
        ippsMinMax_16s(buffer, length, min, max);
    }

    void minmax(const int32_t *buffer, size_t length, int32_t *min, int32_t *max) {
        ippsMinMax_32s(buffer, length, min, max);
    }

    void minmax(const uint16_t *buffer, size_t length, uint16_t *min, uint16_t *max) {
        ippsMinMax_16u(buffer, length, min, max);
    }

    void minmax(const uint32_t *buffer, size_t length, uint32_t *min, uint32_t *max) {
        ippsMinMax_32u(buffer, length, min, max);
    }

    void minmax(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, wipp_complex_t *max) {
        Ipp64f magnitude[length];
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), magnitude, length);
        int maximum_index, minimum_index;
        Ipp64f maximum_value, minimum_value;
        ippsMinMaxIndx_64f(magnitude, length, &minimum_value, &minimum_index, &maximum_value, &maximum_index);
        *min = buffer[minimum_index];
        *max = buffer[maximum_index];
    }

    struct wipp_rand_t_ {
        wipp_rand_t_() :
        state_size(0),
        state64f(nullptr)
        {
            ippsRandGaussGetSize_64f(&state_size);
            state64f = reinterpret_cast<IppsRandGaussState_64f*>(ippsMalloc_8u(state_size));
        }
        int state_size;
        IppsRandGaussState_64f *state64f;
    };

    void init_rand_gaussian(wipp_rand_t **rand, double mean, double stddev) {
        *rand = new wipp_rand_t();
        ippsRandGaussInit_64f((*rand)->state64f, mean, stddev, 7119);
    }

    void init_rand_gaussian(wipp_rand_t **rand, float mean, float stddev) {
        *rand = new wipp_rand_t();;
        ippsRandGaussInit_64f((*rand)->state64f, mean, stddev, 7119);
    }

    void init_rand_gaussian(wipp_rand_t **rand, int mean, int stddev) {
        init_rand_gaussian(rand, static_cast<double>(mean), static_cast<double>(stddev));
    }

    void delete_rand(wipp_rand_t **rand) {
        if (rand != nullptr && *rand != nullptr) {
            ippsFree((*rand)->state64f);
            delete *rand;
        }
        *rand = nullptr;
    }

    void rand(wipp_rand_t *rand, double *buffer, size_t length) {
        auto errorValue = ippsRandGauss_64f(buffer, length, rand->state64f);
        if (errorValue != ippStsNoErr)
            throw(WIppException(ippGetStatusString(errorValue)));
    }

    void rand(wipp_rand_t *rand, float *buffer, size_t length) {
        Ipp64f intermediate_buffer[length];
        ippsRandGauss_64f(intermediate_buffer, length, rand->state64f);
        copyBuffer(intermediate_buffer, buffer, length);
    }

    void rand(wipp_rand_t *rand, int *buffer, size_t length) {
        Ipp64f intermediate_buffer[length];
        ippsRandGauss_64f(intermediate_buffer, length, rand->state64f);
        copyBuffer(intermediate_buffer, buffer, length);
    }

}