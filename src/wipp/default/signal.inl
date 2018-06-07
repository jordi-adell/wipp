/*
* signal.inl
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
#include <wipp/wippstats.h>
#include <wipp/wippmeldefs.h>

namespace wipp
{


void power(const wipp_complex_t *spectrum, double *power, size_t length)
{
    for (size_t i = 0; i < length; ++i)
	power[i] = spectrum[i].re * spectrum[i].re + spectrum[i].im * spectrum[i].im;
}

void power(const double *buffer, double *power, size_t length)
{
    for (size_t i = 0; i < length; ++i)
	power[i] = buffer[i]*buffer[i];
}

void power(double *buffer, size_t length)
{
    power(buffer, buffer, length);
}

template <typename T>
void magnitude_core(const wipp_complex_t *buffer, T *magnitude, size_t length)
{
    for (size_t i = 0; i < length; ++i)
	magnitude[i] = sqrt(buffer[i].re*buffer[i].re + buffer[i].im*buffer[i].im);
}

void magnitude(const wipp_complex_t *buffer, double *magnitude, size_t length)
{ magnitude_core(buffer, magnitude, length); }
void magnitude(const wipp_complex_t *buffer, float *magnitude, size_t length)
{ magnitude_core(buffer, magnitude, length); }


template<typename T>
void ramp_core(T *buffer, size_t length, double offset, double slope)
{
    for (size_t i = 0; i < length; ++i)
    {
	buffer[i] = slope*i + offset;
    }
}

void ramp(double *buffer, size_t length, double offset, double slope) {ramp_core(buffer, length, offset, slope);}
void ramp(float *buffer, size_t length, double offset, double slope) {ramp_core(buffer, length, offset, slope);}
void ramp(int *buffer, size_t length, double offset, double slope) {ramp_core(buffer, length, offset, slope);}
void ramp(uint16_t *buffer, size_t length, double offset, double slope) {ramp_core(buffer, length, offset, slope);}



/**
 * @brief triangle   triangle that goes from -1 to 1 and then back to -1 in period samples.
 * You can shift it using the phase value.
 * @param buffer
 * @param length   number of samples to use, can be equal or lower than period. If larger, the remaining will be filled with zeros.
 * @param period   length of the triangle.
 * @param phase    sample shift of the triangle.
 * @param asym
 * @param offset
 */
void triangle(double *buffer, size_t length, int period, double phase, double asym, double offset)
{
    phase = (phase >= 2*M_PI) ? 0.99*2*M_PI : phase;
    phase = (phase <= 0)      ?        0.01 : phase;

    asym = (asym > M_PI)  ?  M_PI : asym;
    asym = (asym < -M_PI) ? -M_PI : asym;

    double n = period*(phase/(4*M_PI)); // i-> buffer index, n -> sample within triangle period?
//    size_t n = d_n;
    size_t i = 0;
    const double center = period*((asym+M_PI)/(2*M_PI)) ;
    const double slope_to_center   = 1.0F/static_cast<double>(center);
    const double slope_from_center = 1.0F/static_cast<double>(period-center);

//    std::cout << period << " " << asym << " " << center << std::endl;
//    std::cout << "slopes: " << slope_to_center << " " << slope_from_center << std::endl;

    const double b = offset + slope_to_center*n;
    const double c = 1 + offset - slope_from_center*(n-center-1);

//    std::cout << "b: " << b << ", c: " << c << ", n: " << n << std::endl;


    if (n <= center)
	buffer[i] = b;
    else
	buffer[i] = c;

    ++n; ++i;


    while (i < length)
    {
	// y = ax + b
	for (; n <= center && i < length; ++i, ++n)
	{
	    buffer[i] = slope_to_center + buffer[i-1];
//	    std::cout << "i: " << i << ", n:" << n << ", t[i]: " << buffer[i] << ", a:" << slope_to_center << std::endl;
	}

	if (i < length)
	{
	    buffer[i] = 1 + offset - slope_from_center*(n-center);
	    ++i; ++n;

	    //y = -ax + c
	    for (; n <= period && i < length; ++i, ++n)
	    {
		buffer[i] = -slope_from_center + buffer[i-1];
//		std::cout << "i: " << i << ", n:" << n << ", t[i]: " << buffer[i] << ", b:" << -slope_from_center << std::endl;
	    }

	    if (i < length)
	    {
		n = n - period;
		buffer[i] = offset + n*slope_to_center;
	    }
	    ++i; ++n;
	}

    }

//    std::cout << "I: " << i << ", N: " << n << std::endl;
}


void triangle(double *buffer, size_t length)
{
    triangle(buffer, length, length, 0, 0, 0);
}


template <typename T>
void tone_core(T *buffer, size_t length, double magnitud, double frequency, double phase)
{
    while(phase < -M_PI) phase += 2*M_PI;
    while(phase > M_PI) phase -= 2*M_PI;
    for (size_t i = 0; i < length; ++i)
    {
	buffer[i] = static_cast<T>(magnitud*sin(2*M_PI*frequency*static_cast<double>(i) + phase));
    }
}

void tone(double *buffer, size_t length, double magnitude, double frequency, double phase){ tone_core(buffer, length, magnitude, frequency, phase); }
void tone(float *buffer, size_t length, double magnitude, double frequency, double phase){ tone_core(buffer, length, magnitude, frequency, phase); }
void tone(int32_t *buffer, size_t length, double magnitude, double frequency, double phase){ tone_core(buffer, length, magnitude, frequency, phase); }
void tone(int16_t *buffer, size_t length, double magnitude, double frequency, double phase){ tone_core(buffer, length, magnitude, frequency, phase); }

template<typename T>
void threshold_lt_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value)
{
    for (size_t i = 0; i < length; ++i)
	buffer_out[i] = (buffer_in[i] < threshold) ? value : buffer_in[i];
}

template<typename T>
void threshold_lt_core(T *buffer, size_t length, T threshold, T value)
{
    threshold_lt_core(buffer, buffer, length, threshold, value);
}

void threshold_lt(double *buffer, size_t length, double threshold, double value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(float *buffer, size_t length, float threshold, float value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(int16_t *buffer, size_t length, int16_t threshold, int16_t value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(int32_t *buffer, size_t length, int32_t threshold, int32_t value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) { threshold_lt_core(buffer, length, threshold, value); }
void threshold_lt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_lt_core(buffer_in, buffer_out, length, threshold, value); }


template<typename T>
void threshold_gt_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value)
{
    for (size_t i = 0; i < length; ++i)
	buffer_out[i] = (buffer_in[i] > threshold) ? value : buffer_in[i];
}

template<typename T>
void threshold_gt_core(T *buffer, size_t length, T threshold, T value)
{
    threshold_gt_core(buffer, buffer, length, threshold, value);
}

void threshold_gt(double *buffer, size_t length, double threshold, double value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(float *buffer, size_t length, float threshold, float value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(int16_t *buffer, size_t length, int16_t threshold, int16_t value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(int32_t *buffer, size_t length, int32_t threshold, int32_t value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) { threshold_gt_core(buffer, length, threshold, value); }
void threshold_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_gt_core(buffer_in, buffer_out, length, threshold, value); }


template<typename T>
void threshold_let_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value)
{
    for (size_t i = 0; i < length; ++i)
	buffer_out[i] = (buffer_in[i] <= threshold) ? value : buffer_in[i];
}

template<typename T>
void threshold_let_core(T *buffer, size_t length, T threshold, T value)
{
    threshold_let_core(buffer, buffer, length, threshold, value);
}

void threshold_let(double *buffer, size_t length, double threshold, double value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(float *buffer, size_t length, float threshold, float value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(int16_t *buffer, size_t length, int16_t threshold, int16_t value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(int32_t *buffer, size_t length, int32_t threshold, int32_t value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) { threshold_let_core(buffer, length, threshold, value); }
void threshold_let(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_let_core(buffer_in, buffer_out, length, threshold, value); }


template<typename T>
void threshold_get_core(const T *buffer_in, T *buffer_out, size_t length, T threshold, T value)
{
    for (size_t i = 0; i < length; ++i)
	buffer_out[i] = (buffer_in[i] >= threshold) ? value : buffer_in[i];
}

template<typename T>
void threshold_get_core(T *buffer, size_t length, T threshold, T value)
{
    threshold_get_core(buffer, buffer, length, threshold, value);
}

void threshold_get(double *buffer, size_t length, double threshold, double value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(float *buffer, size_t length, float threshold, float value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(int16_t *buffer, size_t length, int16_t threshold, int16_t value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(int32_t *buffer, size_t length, int32_t threshold, int32_t value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(uint16_t *buffer, size_t length, uint16_t threshold, uint16_t value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(uint32_t *buffer, size_t length, uint32_t threshold, uint32_t value) { threshold_get_core(buffer, length, threshold, value); }
void threshold_get(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_get_core(buffer_in, buffer_out, length, threshold, value); }


template<typename T>
void threshold_lt_gt_core(const T *buffer_in, T *buffer_out, size_t length,
			  T threshold_lt, T value_lt, T threshold_gt, T value_gt)
{
    for (size_t i = 0; i < length; ++i)
    {
	buffer_out[i] = (buffer_in[i] < threshold_lt) ? value_lt : buffer_in[i];
	buffer_out[i] = (buffer_in[i] > threshold_gt) ? value_gt : buffer_out[i];
    }
}

template<typename T>
void threshold_lt_gt_core(T *buffer, size_t length,
			  T threshold_lt, T value_lt, T threshold_gt, T value_gt)
{
    T value;
    for (size_t i = 0; i < length; ++i)
    {
	value = buffer[i];
	buffer[i] = (value < threshold_lt) ? value_lt : buffer[i];
	buffer[i] = (value > threshold_gt) ? value_gt : buffer[i];
    }
}

void threshold_lt_gt(double *buffer, size_t length, double threshold_lt, double value_lt, double threshold_gt, double value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(float *buffer, size_t length, float threshold_lt, float value_lt, float threshold_gt, float value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(int16_t *buffer, size_t length, int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(int32_t *buffer, size_t length, int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(uint16_t *buffer, size_t length, uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(uint32_t *buffer, size_t length, uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt)
{ threshold_lt_gt_core(buffer, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold_lt, double value_lt, double threshold_gt, double value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold_lt, float value_lt, float threshold_gt, float value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold_lt, int16_t value_lt, int16_t threshold_gt, int16_t value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold_lt, int32_t value_lt, int32_t threshold_gt, int32_t value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold_lt, uint16_t value_lt, uint16_t threshold_gt, uint16_t value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }
void threshold_lt_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold_lt, uint32_t value_lt, uint32_t threshold_gt, uint32_t value_gt)
{ threshold_lt_gt_core(buffer_in, buffer_out, length, threshold_lt, value_lt, threshold_gt, value_gt); }

template<typename T>
void threshold_let_get_core(const T *buffer_in, T *buffer_out, size_t length,
			  T threshold_let, T value_let, T threshold_get, T value_get)
{
    for (size_t i = 0; i < length; ++i)
    {
	buffer_out[i] = (buffer_in[i] < threshold_let) ? value_let : buffer_in[i];
	buffer_out[i] = (buffer_in[i] > threshold_get) ? value_get : buffer_out[i];
    }
}

template<typename T>
void threshold_let_get_core(T *buffer, size_t length,
			  T threshold_let, T value_let, T threshold_get, T value_get)
{
    threshold_let_get_core(buffer, buffer, length, threshold_let, value_let, threshold_get, value_get);
}

void threshold_let_get(double *buffer, size_t length, double threshold_let, double value_let, double threshold_get, double value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(float *buffer, size_t length, float threshold_let, float value_let, float threshold_get, float value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(int16_t *buffer, size_t length, int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(int32_t *buffer, size_t length, int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(uint16_t *buffer, size_t length, uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(uint32_t *buffer, size_t length, uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get)
{ threshold_let_get_core(buffer, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const double *buffer_in, double *buffer_out, size_t length, double threshold_let, double value_let, double threshold_get, double value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const float *buffer_in, float *buffer_out, size_t length, float threshold_let, float value_let, float threshold_get, float value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold_let, int16_t value_let, int16_t threshold_get, int16_t value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold_let, int32_t value_let, int32_t threshold_get, int32_t value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold_let, uint16_t value_let, uint16_t threshold_get, uint16_t value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }
void threshold_let_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold_let, uint32_t value_let, uint32_t threshold_get, uint32_t value_get)
{ threshold_let_get_core(buffer_in, buffer_out, length, threshold_let, value_let, threshold_get, value_get); }



template <typename T>
void linear2mel_core(const T *linear, T *mel, size_t length, const T* mult, const T*div)
{
    for (size_t i = 0; i < length; ++i)
	mel[i] = (*mult) * log( 1 + linear[i]/(*div) ) / log(10);
}

void linear2mel(const double *linear, double *mel, size_t length, const double* mult, const double*div) { linear2mel_core(linear, mel, length, mult, div);}
void linear2mel(const double *linear, double *mel, size_t length) { linear2mel(linear, mel, length, &default_mel_mult64, &default_mel_div64);}
void linear2mel(const float *linear, float *mel, size_t length, const float* mult, const float*div) { linear2mel_core(linear, mel, length, mult, div);}
void linear2mel(const float *linear, float *mel, size_t length) { linear2mel(linear, mel, length, &default_mel_mult32, &default_mel_div32);}

template <typename T>
void mel2linear_core(const T *mel, T *linear, size_t length, const T* mult, const T*div)
{
    for (size_t i = 0; i < length; ++i)
	linear[i] = ( exp( mel[i] * log(10) / (*mult) ) - 1 )*(*div);
}

void mel2linear(const double *mel, double *linear, size_t length, const double* mult, const double*div) { mel2linear_core(mel, linear, length, mult, div);}
void mel2linear(const double *mel, double *linear, size_t length) { mel2linear(mel, linear, length, &default_mel_mult64, &default_mel_div64);}
void mel2linear(const float *mel, float *linear, size_t length, const float* mult, const float*div) { mel2linear_core(mel, linear, length, mult, div);}
void mel2linear(const float *mel, float *linear, size_t length) { mel2linear(mel, linear, length, &default_mel_mult32, &default_mel_div32);}


template <typename T>
void cross_corr_core(const T *buffer1, size_t length1,
		     const T *buffer2, size_t length2,
		     T *corr, size_t corr_length, int lowLag)
{
    int j = 0;
    for (size_t iCorr = 0; iCorr < corr_length; ++iCorr)
    {
	corr[iCorr] = 0;
	for (size_t i = 0; i < length1; ++i)
	{
	    //TODO:Use wipp::mult here
	    j = iCorr + i + lowLag;
	    if (0 <= j && j < length2)
	    {
		corr[iCorr] += buffer1[i]*buffer2[j];
	    }
	}
    }
}

void cross_corr(const double *buffer1, size_t length1, double *buffer2, size_t length2, double *corr, size_t corr_length, int lowLag)
{cross_corr_core(buffer1, length1, buffer2, length2, corr, corr_length, lowLag); }
void cross_corr(const float *buffer1, size_t length1, float *buffer2, size_t length2, float *corr, size_t corr_length, int lowLag)
{cross_corr_core(buffer1, length1, buffer2, length2, corr, corr_length, lowLag); }
void cross_corr(const int16_t *buffer1, size_t length1, int16_t *buffer2, size_t length2, int16_t *corr, size_t corr_length, int lowLag)
{cross_corr_core(buffer1, length1, buffer2, length2, corr, corr_length, lowLag); }
void cross_corr(const int32_t *buffer1, size_t length1, int32_t *buffer2, size_t length2, int32_t *corr, size_t corr_length, int lowLag)
{cross_corr_core(buffer1, length1, buffer2, length2, corr, corr_length, lowLag); }
void cross_corr(const uint16_t *buffer1, size_t length1, uint16_t *buffer2, size_t length2, uint16_t *corr, size_t corr_length, int lowLag)
{cross_corr_core(buffer1, length1, buffer2, length2, corr, corr_length, lowLag); }


template <typename T>
void median_filter_core(const T* inbuffer, T* outbuffer, size_t length, int maskSize) {
    maskSize = 2* (maskSize/2) + 1; // make it next odd number.
    size_t start = maskSize/2; // get center of the mask.
    size_t end = length - start;
    T tmp_buff[2*start + length];

    memcpy(&tmp_buff[start], inbuffer, length*sizeof(T));

    for (int i = 0; i < start; ++i) {
        outbuffer[i] = tmp_buff[i] = inbuffer[0];
        tmp_buff[length + start + i] = inbuffer[length - 1];
    }

    for (int i = 0; i < length - start; ++i)
        median(&tmp_buff[i], maskSize, &outbuffer[i + start]);
}


template <typename T>
void median_filter_core(T* buffer, size_t length, int maskSize)
{
    T outbuffer[length];
    median_filter_core(buffer, outbuffer, length, maskSize);
    memcpy(reinterpret_cast<void*>(buffer), reinterpret_cast<const void*>(outbuffer), sizeof(T)*length);
}


void median_filter(const double *inbuffer, double *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}
void median_filter(const float *inbuffer, float *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}
void median_filter(const int16_t *inbuffer, int16_t *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}
void median_filter(const int32_t *inbuffer, int32_t *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}
void median_filter(const uint16_t *inbuffer, uint16_t *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}
void median_filter(const uint32_t *inbuffer, uint32_t *outbuffer, size_t length, int maskSize)
{median_filter_core(inbuffer, outbuffer, length, maskSize);}


void median_filter( double *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}
void median_filter( float *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}
void median_filter( int16_t *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}
void median_filter( int32_t *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}
void median_filter( uint16_t *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}
void median_filter( uint32_t *buffer, size_t length, int maskSize)
{median_filter_core(buffer, length, maskSize);}





}
