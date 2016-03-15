#include <wipp/wippstats.h>
#include <wipp/wipputils.h>

#include <limits>
#include <math.h>

namespace wipp
{

template<typename T>
void sum_core(const T *buffer, size_t length, T* sum)
{
    *sum = 0;
    for (size_t i = 0; i  < length; ++i)
	*sum += buffer[i];
}

void sum(const double *buffer, size_t length, double *sum){ sum_core(buffer, length, sum); }
void sum(const float *buffer, size_t length, float *sum){ sum_core(buffer, length, sum); }
void sum(const int16_t *buffer, size_t length, int16_t *sum){ sum_core(buffer, length, sum); }
void sum(const int32_t *buffer, size_t length, int32_t *sum){ sum_core(buffer, length, sum); }
void sum(const uint16_t *buffer, size_t length, uint16_t *sum){ sum_core(buffer, length, sum); }
void sum(const uint32_t *buffer, size_t length, uint32_t *sum){ sum_core(buffer, length, sum); }
void sum(const wipp_complex_t *buffer, size_t length, wipp_complex_t *sum)
{
    sum->re = sum->im = 0;
    for (size_t i = 0; i < length; ++i)
    {
	sum->re = buffer[i].re;
	sum->im = buffer[i].im;
    }
}



template<typename T>
void mean_core(const T *buffer, size_t length, T* mean)
{
    sum_core(buffer, length, mean);
    *mean /= length;
}

void mean(const double *buffer, size_t length, double *mean){ mean_core(buffer, length, mean); }
void mean(const float *buffer, size_t length, float *mean){ mean_core(buffer, length, mean); }
void mean(const int16_t *buffer, size_t length, int16_t *mean){ mean_core(buffer, length, mean); }
void mean(const int32_t *buffer, size_t length, int32_t *mean){ mean_core(buffer, length, mean); }
void mean(const uint16_t *buffer, size_t length, uint16_t *mean){ mean_core(buffer, length, mean); }
void mean(const uint32_t *buffer, size_t length, uint32_t *mean){ mean_core(buffer, length, mean); }
void mean(const wipp_complex_t *buffer, size_t length, wipp_complex_t *mean)
{
    sum(buffer, length, mean);
    mean->re /= length;
    mean->im /= length;
}




template<typename T>
void var_core(const T *buffer, size_t length, T* var)
{
    // var(c) = E[x^2] - E^2[x]
    T mean_value;
    double mean2 = 0;
    mean(buffer, length, &mean_value);
    for (size_t i = 0; i < length; ++i)
    {
	mean2 += static_cast<double>(buffer[i])*static_cast<double>(buffer[i]);
    }
    mean2 /= length;

    *var = mean2 - pow(static_cast<double>(mean_value),2);
}

void var(const double *buffer, size_t length, double *var){ var_core(buffer, length, var); }
void var(const float *buffer, size_t length, float *var){ var_core(buffer, length, var); }
void var(const int16_t *buffer, size_t length, int16_t *var){ var_core(buffer, length, var); }
void var(const int32_t *buffer, size_t length, int32_t *var){ var_core(buffer, length, var); }
void var(const uint16_t *buffer, size_t length, uint16_t *var){ var_core(buffer, length, var); }
void var(const uint32_t *buffer, size_t length, uint32_t *var){ var_core(buffer, length, var); }
void var(const wipp_complex_t *buffer, size_t length, wipp_complex_t *var)
{
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




template<typename T>
void min_core(const T *buffer, size_t length, T *min)
{
    *min = std::numeric_limits<T>::max();
    for (size_t i = 0; i < length; ++i)
	*min = (buffer[i] < *min) ? buffer[i] : *min;
}

void min(const double *buffer, size_t length, double *min) { min_core(buffer, length, min); }
void min(const float *buffer, size_t length, float *min) { min_core(buffer, length, min); }
void min(const int16_t *buffer, size_t length, int16_t *min) { min_core(buffer, length, min); }
void min(const int32_t *buffer, size_t length, int32_t *min) { min_core(buffer, length, min); }
void min(const uint16_t *buffer, size_t length, uint16_t *min) { min_core(buffer, length, min); }
void min(const uint32_t *buffer, size_t length, uint32_t *min) { min_core(buffer, length, min); }
void min(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min)
{
    double minmagn = std::numeric_limits<double>::max();
    double magn;
    for (size_t i = 0;i < length; ++i)
    {
	magn = std::sqrt(buffer[i].re*buffer[i].re + buffer[i].im*buffer[i].im);
	if (magn < minmagn)
	{
	    minmagn = magn;
	    *min = buffer[i];
	}
    }
}




template<typename T>
void max_core(const T *buffer, size_t length, T *max)
{
    *max = std::numeric_limits<T>::min();
    for (size_t i = 0; i < length; ++i)
	*max = (buffer[i] > *max) ? buffer[i] : *max;
}

void max(const double *buffer, size_t length, double *max) { max_core(buffer, length, max); }
void max(const float *buffer, size_t length, float *max) { max_core(buffer, length, max); }
void max(const int16_t *buffer, size_t length, int16_t *max) { max_core(buffer, length, max); }
void max(const int32_t *buffer, size_t length, int32_t *max) { max_core(buffer, length, max); }
void max(const uint16_t *buffer, size_t length, uint16_t *max) { max_core(buffer, length, max); }
void max(const uint32_t *buffer, size_t length, uint32_t *max) { max_core(buffer, length, max); }
void max(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max)
{
    double maxmagn = std::numeric_limits<double>::min();
    double magn;
    for (size_t i = 0;i < length; ++i)
    {
	magn = std::sqrt(buffer[i].re*buffer[i].re + buffer[i].im*buffer[i].im);
	if (magn > maxmagn)
	{
	    maxmagn = magn;
	    *max = buffer[i];
	}
    }
}


template<typename T>
void minmax_core(const T *buffer, size_t length, T *min, T *max)
{
    *max = std::numeric_limits<T>::min();
    *min = std::numeric_limits<T>::max();
    for (size_t i = 0; i < length; ++i)
    {
	*max = (buffer[i] > *max) ? buffer[i] : *max;
	*min = (buffer[i] < *min) ? buffer[i] : *min;
    }
}

void minmax(const double *buffer, size_t length, double *min, double *max) { minmax_core(buffer, length, min, max); }
void minmax(const float *buffer, size_t length, float *min, float *max) { minmax_core(buffer, length, min, max); }
void minmax(const int16_t *buffer, size_t length, int16_t *min, int16_t *max) { minmax_core(buffer, length, min, max); }
void minmax(const int32_t *buffer, size_t length, int32_t *min, int32_t *max) { minmax_core(buffer, length, min, max); }
void minmax(const uint16_t *buffer, size_t length, uint16_t *min, uint16_t *max) { minmax_core(buffer, length, min, max); }
void minmax(const uint32_t *buffer, size_t length, uint32_t *min, uint32_t *max) { minmax_core(buffer, length, min, max); }
void minmax(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, wipp_complex_t *max)
{
    double maxmagn = std::numeric_limits<double>::min();
    double minmagn = std::numeric_limits<double>::max();
    double magn;
    for (size_t i = 0;i < length; ++i)
    {
	magn = std::sqrt(buffer[i].re*buffer[i].re + buffer[i].im*buffer[i].im);
	if (magn > maxmagn)
	{
	    maxmagn = magn;
	    *max = buffer[i];
	}
	if (magn < minmagn)
	{
	    minmagn = magn;
	    *min = buffer[i];
	}
    }
}



}
