/*
* ippsignal.inl
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
#include <wipp/wippsignal.h>
#include <wipp/wipputils.h>
#include <wipp/wippmeldefs.h>

#include <ipps.h>

#include <limits>

namespace wipp {

    void power(const wipp_complex_t *buffer, double *power, size_t length) {
        ippsPowerSpectr_64fc(reinterpret_cast<const Ipp64fc*>(buffer), power, length);
    }
    void power(const double *buffer, double *power, size_t length) {
        ippsSqr_64f(buffer, power, length);
    }

    void power(double *buffer, size_t length) {
        ippsSqr_64f_I(buffer, length);
    }

    void magnitude(const wipp_complex_t* buffer, double *magnitude, size_t length) {
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), magnitude, length);
    }

    void magnitude(const wipp_complex_t* buffer, float *magnitude, size_t length) {
        Ipp64f intermediateBuffer[length];
        ippsMagnitude_64fc(reinterpret_cast<const Ipp64fc*>(buffer), intermediateBuffer, length);
        ippsConvert_64f32f(intermediateBuffer, magnitude, length);
    }

    void ramp(double *buffer, size_t length, double offset, double slope) {
        ippsVectorSlope_64f(buffer, length,offset, slope);
    }
    void ramp(float *buffer, size_t length, double offset, double slope) {
        ippsVectorSlope_32f(buffer, length, offset, slope);
    }
    void ramp(int *buffer, size_t length, double offset, double slope) {
        ippsVectorSlope_32s(buffer, length, offset, slope);
    }
    void ramp(uint16_t *buffer, size_t length, double offset, double slope) {
        ippsVectorSlope_16u(buffer, length, offset, slope);
    }


    void triangle(double *buffer, size_t length, int period, double phase, double asym, double offset) {
        ippsTriangle_64f(buffer, length, 1.0, 1.0/period, asym, &phase);
    }

    void triangle(double *buffer, size_t length) {
        triangle(buffer, length, length, 3*M_PI_2, 0, 0);
    }


    void tone(double *buffer, size_t length, double magnitude, double frequency, double phase) {
        ippsTone_64f(buffer, length, magnitude, frequency, &phase, ippAlgHintFast);
    }

    void tone(float *buffer, size_t length, double magnitude, double frequency, double phase) {
        Ipp32f floatPhase = static_cast<Ipp32f>(phase);
        ippsTone_32f(buffer, length, magnitude, frequency, &floatPhase, ippAlgHintFast);
    }
    void tone(int32_t *buffer, size_t length, double magnitude, double frequency, double phase) {
        Ipp64f intermediateBuffer[length];
        ippsTone_64f(intermediateBuffer, length, magnitude, frequency, &phase, ippAlgHintFast);
        ippsConvert_64f32s_Sfs(intermediateBuffer, buffer, length, ippRndFinancial, 0);
    }

    void tone(int16_t *buffer, size_t length, double magnitude, double frequency, double phase) {
        Ipp32f intPhase = phase;
        ippsTone_16s(buffer, length, magnitude, frequency, &intPhase, ippAlgHintFast);
    }

    void threshold_lt(double *buffer, size_t length, double threshold, double value) {
        ippsThreshold_LTVal_64f_I(buffer,length, threshold, value);
    }

    void threshold_lt(float *buffer, size_t length, float threshold, float value) {
        ippsThreshold_LTVal_32f_I(buffer, length, threshold, value);
    }

    void threshold_lt(int16_t *buffer, size_t length, int16_t threshold, int16_t value) {
        ippsThreshold_LTVal_16s_I(buffer, length, threshold, value);
    }

    void threshold_lt(int32_t *buffer, size_t length, int32_t threshold, int32_t value) {
        ippsThreshold_LTValGTVal_32s_I(buffer,length, threshold, value,
                                       std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max());
    }

    void threshold_lt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer[i]);
        threshold_lt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];

    }

    void threshold_lt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer[i]);
        threshold_lt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];
    }

    void threshold_lt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) {
        ippsThreshold_LTVal_64f(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_lt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) {
        ippsThreshold_LTVal_32f(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_lt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) {
        ippsThreshold_LTVal_16s(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_lt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) {
        ippsThreshold_LTValGTVal_32s(buffer_in, buffer_out, length, threshold, value,
                                       std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max());
    }

    void threshold_lt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer_in[i]);
        threshold_lt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }

    void threshold_lt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer_in[i]);
        threshold_lt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }


    void threshold_gt(double *buffer, size_t length, double threshold, double value) {
        ippsThreshold_GTVal_64f_I(buffer,length, threshold, value);
    }

    void threshold_gt(float *buffer, size_t length, float threshold, float value) {
        ippsThreshold_GTVal_32f_I(buffer, length, threshold, value);
    }

    void threshold_gt(int16_t *buffer, size_t length, int16_t threshold, int16_t value) {
        ippsThreshold_GTVal_16s_I(buffer, length, threshold, value);
    }

    void threshold_gt(int32_t *buffer, size_t length, int32_t threshold, int32_t value) {
        ippsThreshold_LTValGTVal_32s_I(buffer,length, threshold, value,
                                       std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max());
    }

    void threshold_gt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer[i]);
        threshold_gt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];

    }

    void threshold_gt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer[i]);
        threshold_gt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];
    }

    void threshold_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) {
        ippsThreshold_GTVal_64f(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) {
        ippsThreshold_GTVal_32f(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) {
        ippsThreshold_GTVal_16s(buffer_in, buffer_out, length, threshold, value);
    }

    void threshold_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) {
        ippsThreshold_LTValGTVal_32s(buffer_in, buffer_out, length, threshold, value,
                                     std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max());
    }

    void threshold_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer_in[i]);
        threshold_gt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }

    void threshold_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer_in[i]);
        threshold_gt(intermediateBuffer, length, threshold, value);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }


    template<typename T>
    void threshold_let_core(T *buffer, size_t length, T threshold, T value) {
        threshold_lt(buffer, length, threshold, value);
        for (size_t i = 0; i < length && threshold != value; ++i)
            buffer[i] = (buffer[i] == threshold) ? value : buffer[i];
    }

    template<typename T>
    void threshold_let_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value) {
        threshold_lt(buffer_in, buffer_out, length, threshold, value);
        for (size_t i = 0; i < length && threshold != value; ++i)
            buffer_out[i] = (buffer_out[i] == threshold) ? value : buffer_out[i];
    }

    void threshold_let(double *buffer, size_t length, double threshold, double value)
    {threshold_let_core(buffer, length, threshold, value);}
    void threshold_let(float *buffer, size_t length, float threshold, float value)
    {threshold_let_core(buffer, length, threshold, value);}
    void threshold_let(int16_t *buffer, size_t length, int16_t threshold, int16_t value)
    {threshold_let_core(buffer, length, threshold, value);}
    void threshold_let(int32_t *buffer, size_t length, int32_t threshold, int32_t value)
    {threshold_let_core(buffer, length, threshold, value);}
    void threshold_let(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value)
    {threshold_let_core(buffer, length, threshold, value);}
    void threshold_let(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value)
    {threshold_let_core(buffer, length, threshold, value);}

    void threshold_let(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_let(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_let(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_let(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_let(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_let(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value)
    {threshold_let_core(buffer_in, buffer_out, length, threshold, value);}

    template<typename T>
    void threshold_get_core(T *buffer, size_t length, T threshold, T value) {
        threshold_gt(buffer, length, threshold, value);
        for (size_t i = 0; i < length && threshold != value; ++i)
            buffer[i] = (buffer[i] == threshold) ? value : buffer[i];
    }

    template<typename T>
    void threshold_get_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value) {
        threshold_gt(buffer_in, buffer_out, length, threshold, value);
        for (size_t i = 0; i < length && threshold != value; ++i)
            buffer_out[i] = (buffer_out[i] == threshold) ? value : buffer_out[i];
    }

    void threshold_get(double *buffer, size_t length, double threshold, double value)
    {threshold_get_core(buffer, length, threshold, value);}
    void threshold_get(float *buffer, size_t length, float threshold, float value)
    {threshold_get_core(buffer, length, threshold, value);}
    void threshold_get(int16_t *buffer, size_t length, int16_t threshold, int16_t value)
    {threshold_get_core(buffer, length, threshold, value);}
    void threshold_get(int32_t *buffer, size_t length, int32_t threshold, int32_t value)
    {threshold_get_core(buffer, length, threshold, value);}
    void threshold_get(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value)
    {threshold_get_core(buffer, length, threshold, value);}
    void threshold_get(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value)
    {threshold_get_core(buffer, length, threshold, value);}

    void threshold_get(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_get(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}
    void threshold_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value)
    {threshold_get_core(buffer_in, buffer_out, length, threshold, value);}


    void threshold_lt_gt(double *buffer, size_t length, double threshold_lt, double value_lt, double threshold_gt, double value_gt) {
        ippsThreshold_LTValGTVal_64f_I(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(float *buffer, size_t length, float threshold_lt, float value_lt, float threshold_gt, float value_gt) {
        ippsThreshold_LTValGTVal_32f_I(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(int16_t *buffer, size_t length, int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt) {
        ippsThreshold_LTValGTVal_16s_I(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(int32_t *buffer, size_t length, int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt) {
        ippsThreshold_LTValGTVal_32s_I(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(uint16_t *buffer, size_t length, uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer[i]);
        threshold_lt_gt(intermediateBuffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];
    }
    void threshold_lt_gt(uint32_t *buffer, size_t length, uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer[i]);
        threshold_lt_gt(intermediateBuffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];
    }

    void threshold_lt_gt(const double *buffer_in, double *buffer_out, size_t length,
                         double threshold_lt, double value_lt, double threshold_gt, double value_gt) {
        ippsThreshold_LTValGTVal_64f(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(const float *buffer_in, float *buffer_out, size_t length,
                         float threshold_lt, float value_lt, float threshold_gt, float value_gt) {
        ippsThreshold_LTValGTVal_32f(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length,
                         int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt) {
        ippsThreshold_LTValGTVal_16s(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length,
                         int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt) {
        ippsThreshold_LTValGTVal_32s(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt);
    }

    void threshold_lt_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length,
                         uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt) {
        int16_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int16_t>(buffer_in[i]);
        threshold_lt_gt(intermediateBuffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }

    void threshold_lt_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length,
                         uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt) {
        int32_t intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = static_cast<int32_t>(buffer_in[i]);
        threshold_lt_gt(intermediateBuffer, length, threshold_lt, value_lt, threshold_gt, value_gt);
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = intermediateBuffer[i];
    }


    template<typename T>
    void threshold_let_get_core(T *buffer, size_t length, T threshold_let, T value_let, T threshold_get, T value_get) {
        threshold_lt_gt(buffer, length, threshold_let, value_let, threshold_get, value_get);
        for (size_t i = 0; i < length; ++i) {
            buffer[i] = (buffer[i] == threshold_let) ? value_let : buffer[i];
            buffer[i] = (buffer[i] == threshold_get) ? value_get : buffer[i];
        }
    }

    void threshold_let_get(double *buffer, size_t length, double threshold_let, double value_let, double threshold_get, double value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(float *buffer, size_t length, float threshold_let, float value_let, float threshold_get, float value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(int16_t *buffer, size_t length, int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(int32_t *buffer, size_t length, int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(uint16_t *buffer, size_t length, uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(uint32_t *buffer, size_t length, uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get)
    {threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get);}

    template<typename T>
    void threshold_let_get_core(const T *buffer_in, T *buffer_out, size_t length, T threshold_let, T value_let, T threshold_get, T value_get) {
        threshold_lt_gt(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);
        for (size_t i = 0; i < length; ++i) {
            buffer_out[i] = (buffer_out[i] == threshold_let) ? value_let : buffer_out[i];
            buffer_out[i] = (buffer_out[i] == threshold_get) ? value_get : buffer_out[i];
        }
    }

    void threshold_let_get(const double *buffer_in, double *buffer_out, size_t length,
                           double threshold_let, double value_let, double threshold_get, double value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(const float *buffer_in, float *buffer_out, size_t length,
                           float threshold_let, float value_let, float threshold_get, float value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length,
                           int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length,
                           int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length,
                           uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}
    void threshold_let_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length,
                           uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get)
    {threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get);}


    void linear2mel(const double *linear, double *mel, size_t length, const double* mult, const double*div) {
        ippsDivC_64f(linear, *div, mel, length);
        ippsAddC_64f_I(1, mel, length);
        ippsLn_64f_I(mel, length);
        ippsDivC_64f_I(log(10), mel, length);
        ippsMulC_64f_I(*mult, mel, length);
    }

    void linear2mel(const double *linear, double *mel, size_t length) {
        linear2mel(linear, mel, length, &default_mel_mult64, &default_mel_div64);
    }

    void linear2mel(const float *linear, float *mel, size_t length, const float* mult, const float*div) {
        ippsDivC_32f(linear, *div, mel, length);
        ippsAddC_32f_I(1, mel, length);
        ippsLn_32f_I(mel, length);
        ippsDivC_32f_I(log(10), mel, length);
        ippsMulC_32f_I(*mult, mel, length);
    }
    void linear2mel(const float *linear, float *mel, size_t length) {
        linear2mel(linear, mel, length, &default_mel_mult32, &default_mel_div32);
    }

    template <typename T>
    void mel2linear_core(const T *mel, T *linear, size_t length, const T* mult, const T*div)
    {
        for (size_t i = 0; i < length; ++i)
            linear[i] = ( exp( mel[i] * log(10) / (*mult) ) - 1 )*(*div);
    }

    void mel2linear(const double *mel, double *linear, size_t length, const double* mult, const double*div) {
        ippsMulC_64f(mel,  log(10), linear, length);
        ippsDivC_64f_I(*mult, linear, length);
        ippsExp_64f_I(linear, length);
        ippsSubC_64f_I(1, linear, length);
        ippsMulC_64f_I(*div, linear, length);
    }
    void mel2linear(const double *mel, double *linear, size_t length) {
        mel2linear(mel, linear, length, &default_mel_mult64, &default_mel_div64);
    }
    void mel2linear(const float *mel, float *linear, size_t length, const float* mult, const float*div) {
        ippsMulC_32f(mel,  log(10), linear, length);
        ippsDivC_32f_I(*mult, linear, length);
        ippsExp_32f_I(linear, length);
        ippsSubC_32f_I(1, linear, length);
        ippsMulC_32f_I(*div, linear, length);
    }

    void mel2linear(const float *mel, float *linear, size_t length) {
        mel2linear(mel, linear, length, &default_mel_mult32, &default_mel_div32);
    }

    Ipp8u *cross_corr_allocate_internal_buffer(size_t length, size_t length2, size_t corr_length, int lowLag) {
        int buffer_size;
        ippsCrossCorrNormGetBufferSize(length, length2, corr_length, lowLag, ipp64f, ippAlgAuto | ippiNormNone, &buffer_size);
        return ippsMalloc_8u(buffer_size);
    }

    void cross_corr_free_internal_buffer(Ipp8u *internalBuffer) {
        ippsFree(internalBuffer);
    }

    void cross_corr(const double *buffer1, size_t length, double *buffer2, size_t length2, double *corr, size_t corr_length, int lowLag) {
        auto *internalBuffer = cross_corr_allocate_internal_buffer(length, length2, corr_length, lowLag);
        ippsCrossCorrNorm_64f(buffer1, length, buffer2, length2, corr, corr_length, lowLag, ippAlgAuto, NULL);
        cross_corr_free_internal_buffer(internalBuffer);
    }

    void cross_corr(const float *buffer1, size_t length, float *buffer2, size_t length2, float *corr, size_t corr_length, int lowLag) {
        auto *internalBuffer = cross_corr_allocate_internal_buffer(length, length2, corr_length, lowLag);
        ippsCrossCorrNorm_32f(buffer1, length, buffer2, length2, corr, corr_length, lowLag, ippAlgAuto, NULL);
        cross_corr_free_internal_buffer(internalBuffer);
    }

    void cross_corr(const int32_t *buffer1, size_t length, int32_t *buffer2, size_t length2, int32_t *corr, size_t corr_length, int lowLag) {
        Ipp64f intermediateBuffer1[length];
        Ipp64f intermediateBuffer2[length2];
        Ipp64f highResolutionCorrelation[corr_length];
        ippsConvert_32s64f(buffer1, intermediateBuffer1, length);
        ippsConvert_32s64f(buffer2, intermediateBuffer2, length2);
        cross_corr(intermediateBuffer1, length, intermediateBuffer2, length2, highResolutionCorrelation, corr_length, lowLag);
        ippsConvert_64f32s_Sfs(highResolutionCorrelation, corr, corr_length, ippRndFinancial, 0);
    }

    void cross_corr(const int16_t *buffer1, size_t length, int16_t *buffer2, size_t length2, int16_t *corr, size_t corr_length, int lowLag) {
        Ipp64f intermediateBuffer1[length];
        Ipp64f intermediateBuffer2[length2];
        Ipp64f highResolutionCorrelation[corr_length];
        ippsConvert_16s64f_Sfs(buffer1, intermediateBuffer1, length, 0);
        ippsConvert_16s64f_Sfs(buffer2, intermediateBuffer2, length2, 0);
        cross_corr(intermediateBuffer1, length, intermediateBuffer2, length2, highResolutionCorrelation, corr_length, lowLag);
        ippsConvert_64f16s_Sfs(highResolutionCorrelation, corr, corr_length, ippRndFinancial, 0);
    }
    void cross_corr(const uint16_t *buffer1, size_t length, uint16_t *buffer2, size_t length2, uint16_t *corr, size_t corr_length, int lowLag) {
        Ipp32f intermediateBuffer1[length];
        Ipp32f intermediateBuffer2[length2];
        Ipp32f highResolutionCorrelation[corr_length];
        ippsConvert_16u32f(buffer1, intermediateBuffer1, length);
        ippsConvert_16u32f(buffer2, intermediateBuffer2, length2);
        cross_corr(intermediateBuffer1, length, intermediateBuffer2, length2, highResolutionCorrelation, corr_length, lowLag);
        ippsConvert_32f16u_Sfs(highResolutionCorrelation, corr, corr_length, ippRndFinancial, 0);
    }



    void median_filter(const double *inbuffer, double *outbuffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp64f, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_64f(inbuffer, outbuffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(const float *inbuffer, float *outbuffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp32f, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_32f(inbuffer, outbuffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(const int16_t *inbuffer, int16_t *outbuffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp16s, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_16s(inbuffer, outbuffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(const int32_t *inbuffer, int32_t *outbuffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp32s, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_32s(inbuffer, outbuffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(const uint16_t *inbuffer, uint16_t *outbuffer, size_t length, int maskSize) {
        Ipp32f intermediateBuffer[length];
        ippsConvert_16u32f(inbuffer, intermediateBuffer, length);
        median_filter(intermediateBuffer, length, maskSize);
        ippsConvert_32f16u_Sfs(intermediateBuffer, outbuffer, length, ippRndFinancial, 0);
    }

    void median_filter(const uint32_t *inbuffer, uint32_t *outbuffer, size_t length, int maskSize) {
        Ipp32f intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = inbuffer[i];
        median_filter(intermediateBuffer, length, maskSize);
        for (size_t i = 0; i < length; ++i)
            outbuffer[i] = intermediateBuffer[i];
    }


    void median_filter(double *buffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp64f, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_64f_I(buffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(float *buffer, size_t length, int maskSize){
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp32f, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_32f_I(buffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(int16_t *buffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp16s, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_16s_I(buffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(int32_t *buffer, size_t length, int maskSize) {
        int internalBufferSize;
        ippsFilterMedianGetBufferSize(maskSize, ipp32s, &internalBufferSize);
        Ipp8u *internalBuffer = ippsMalloc_8u(internalBufferSize);
        ippsFilterMedian_32s_I(buffer, length, maskSize, NULL, NULL, internalBuffer);
    }

    void median_filter(uint16_t *buffer, size_t length, int maskSize) {
        Ipp32f intermediateBuffer[length];
        ippsConvert_16u32f(buffer, intermediateBuffer, length);
        median_filter(intermediateBuffer, length, maskSize);
        ippsConvert_32f16u_Sfs(intermediateBuffer, buffer, length, ippRndFinancial, 0);
    }

    void median_filter(uint32_t *buffer, size_t length, int maskSize) {
        Ipp32f intermediateBuffer[length];
        for (size_t i = 0; i < length; ++i)
            intermediateBuffer[i] = buffer[i];
        median_filter(intermediateBuffer, length, maskSize);
        for (size_t i = 0; i < length; ++i)
            buffer[i] = intermediateBuffer[i];
    }





}

