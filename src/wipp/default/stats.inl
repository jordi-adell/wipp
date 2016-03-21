/*
* stats.inl
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
#include <wipp/wippstats.h>
#include <wipp/wipputils.h>

#include <limits>
#include <random>
#include <typeinfo>
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
void stddev_core(const T *buffer, size_t length, T* stddev)
{
    var(buffer, length, stddev);
    *stddev = std::sqrt(*stddev);
}

void stddev(const double *buffer, size_t length, double *stddev){ stddev_core(buffer, length, stddev); }
void stddev(const float *buffer, size_t length, float *stddev){ stddev_core(buffer, length, stddev); }
void stddev(const int16_t *buffer, size_t length, int16_t *stddev){ stddev_core(buffer, length, stddev); }
void stddev(const int32_t *buffer, size_t length, int32_t *stddev){ stddev_core(buffer, length, stddev); }
void stddev(const uint16_t *buffer, size_t length, uint16_t *stddev){ stddev_core(buffer, length, stddev); }
void stddev(const uint32_t *buffer, size_t length, uint32_t *stddev){ stddev_core(buffer, length, stddev); }




template<typename T>
void min_core(const T *buffer, size_t length, T *min, size_t *idx)
{
    *min = std::numeric_limits<T>::max();
    *idx = 0;
    for (size_t i = 0; i < length; ++i)
    {
	*min = (buffer[i] < *min) ? buffer[i] : *min;
	*idx = i;
    }
}

void min(const double *buffer, size_t length, double *min) { size_t idx; min_core(buffer, length, min, &idx); }
void min(const float *buffer, size_t length, float *min) { size_t idx; min_core(buffer, length, min, &idx); }
void min(const int16_t *buffer, size_t length, int16_t *min) { size_t idx; min_core(buffer, length, min, &idx); }
void min(const int32_t *buffer, size_t length, int32_t *min) { size_t idx; min_core(buffer, length, min, &idx); }
void min(const uint16_t *buffer, size_t length, uint16_t *min) { size_t idx; min_core(buffer, length, min, &idx); }
void min(const uint32_t *buffer, size_t length, uint32_t *min) { size_t idx; min_core(buffer, length, min, &idx); }

void min(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, size_t *idx)
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
	    *idx = i;
	}
    }
}
void min(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min)
{ size_t idx; wipp::min(buffer, length, min, &idx); }



template<typename T>
void max_core(const T *buffer, size_t length, T *max, size_t *idx)
{
    *max = std::numeric_limits<T>::min();
    for (size_t i = 0; i < length; ++i)
    {
	*max = (buffer[i] > *max) ? buffer[i] : *max;
	*idx = i;
    }
}

void max(const double *buffer, size_t length, double *max) { size_t idx; max_core(buffer, length, max, &idx); }
void max(const float *buffer, size_t length, float *max) { size_t idx; max_core(buffer, length, max, &idx); }
void max(const int16_t *buffer, size_t length, int16_t *max) { size_t idx; max_core(buffer, length, max, &idx); }
void max(const int32_t *buffer, size_t length, int32_t *max) { size_t idx; max_core(buffer, length, max, &idx); }
void max(const uint16_t *buffer, size_t length, uint16_t *max) { size_t idx; max_core(buffer, length, max, &idx); }
void max(const uint32_t *buffer, size_t length, uint32_t *max) { size_t idx; max_core(buffer, length, max, &idx); }

void max(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max, size_t *idx)
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
	    *idx = i;
	}
    }
}
void max(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max)
{ size_t idx; wipp::max(buffer, length, max, &idx); }



void minidx(const double *buffer, size_t length, double *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const float *buffer, size_t length, float *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const int16_t *buffer, size_t length, int16_t *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const int32_t *buffer, size_t length, int32_t *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const uint16_t *buffer, size_t length, uint16_t *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const uint32_t *buffer, size_t length, uint32_t *min, size_t *idx) { min_core(buffer, length, min, idx); }
void minidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *min, size_t *idx) { wipp::min(buffer, length, min, idx); }


void maxidx(const double *buffer, size_t length, double *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const float *buffer, size_t length, float *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const int16_t *buffer, size_t length, int16_t *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const int32_t *buffer, size_t length, int32_t *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const uint16_t *buffer, size_t length, uint16_t *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const uint32_t *buffer, size_t length, uint32_t *max, size_t *idx) { max_core(buffer, length, max, idx); }
void maxidx(const wipp_complex_t *buffer, size_t length, wipp_complex_t *max, size_t *idx) { wipp::max(buffer, length, max, idx); }




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


typedef enum{
    WIPP_GAUSS
}wipp_rand_dist_t;


template<typename _RealType, class _DistributionType>
struct wipp_rand_t_tmpl_t_
{
	wipp::wipp_rand_dist_t _distr_type;
	size_t _data_type;
	std::random_device _rdevice;
	std::mt19937 *_generator;
	_DistributionType *_distribution;
};


struct wipp_rand_t_
{
	wipp::wipp_rand_dist_t _distr_type;
	size_t _data_type;
	std::random_device _rdevice;
	std::mt19937 *_generator;
	void *_distribution;
};


typedef wipp_rand_t_tmpl_t_<double, std::normal_distribution<double> > wipp_rand_t_gaussian_double_t_;
typedef wipp_rand_t_tmpl_t_<float, std::normal_distribution<float> > wipp_rand_t_gaussian_float_t_;


template<typename T>
void init_rand_gaussian_core(wipp_rand_t_tmpl_t_<T, std::normal_distribution<T> > **rand, T mean, T stddev)
{
    if (rand != NULL)
    {
	    (*rand) = new wipp_rand_t_tmpl_t_<T, std::normal_distribution<T> >();
	    (*rand)->_distr_type = WIPP_GAUSS;
	    (*rand)->_distribution = new std::normal_distribution<T>(mean, stddev);
	    (*rand)->_generator = new std::mt19937((*rand)->_rdevice());
	    (*rand)->_data_type = typeid(T).hash_code();
    }
}


template<typename T>
void delete_rand_core(wipp_rand_t_ *rand)
{
    if (rand)
    {
	switch(rand->_distr_type)
	{
	    case WIPP_GAUSS:
		delete reinterpret_cast<std::normal_distribution<T>*>(rand->_distribution);
		rand->_distribution = NULL;
		delete rand;
		rand = NULL;
	    break;
	    default:
	    break;
	}
    }
}


template<typename T, typename D>
void rand_core_gaussian_data(wipp_rand_t_ *rand, T *buffer, size_t length)
{
    for (size_t i = 0; i < length; ++i)
	buffer[i] =
		(*reinterpret_cast<wipp_rand_t_tmpl_t_<D, std::normal_distribution<D> > *>(rand)
		 ->_distribution)(*rand->_generator);
}


template<typename T>
void rand_core_gaussian(wipp_rand_t_ *rand, T *buffer, size_t length)
{
    if (rand->_data_type == typeid(double).hash_code())
    {
	rand_core_gaussian_data<T,double>(rand, buffer, length);
    }
    else if (rand->_data_type == typeid(float).hash_code())
    {
	rand_core_gaussian_data<T,float>(rand, buffer, length);
    }
}



template<typename T>
void rand_core(wipp_rand_t_ *rand, T *buffer, size_t length)
{
    switch(rand->_distr_type)
    {
	case WIPP_GAUSS:
	    rand_core_gaussian(rand, buffer, length);
	break;
	default:
	break;
    }
}



void init_rand_gaussian(wipp_rand_t **rand, double mean, double stddev)
{ init_rand_gaussian_core(reinterpret_cast<wipp_rand_t_gaussian_double_t_**>(rand), mean, stddev); }
void init_rand_gaussian(wipp_rand_t **rand, float mean, float stddev)
{ init_rand_gaussian_core(reinterpret_cast<wipp_rand_t_gaussian_float_t_**>(rand), mean, stddev); }
void init_rand_gaussian(wipp_rand_t **rand, int mean, int stddev)
{ init_rand_gaussian_core(reinterpret_cast<wipp_rand_t_gaussian_float_t_**>(rand),static_cast<float>(mean), static_cast<float>(stddev)); }


void rand(wipp_rand_t_ *rand, double *buffer, size_t length) { rand_core(rand, buffer, length); }
void rand(wipp_rand_t_ *rand, float *buffer, size_t length) { rand_core(rand, buffer, length); }
void rand(wipp_rand_t_ *rand, int *buffer, size_t length) { rand_core(rand, buffer, length); }


void delete_rand(wipp_rand_t_ **rand)
{
    if (rand != NULL && *rand != NULL)
    {
	switch((*rand)->_distr_type)
	{
	    case WIPP_GAUSS:
		if (typeid(double).hash_code() == (*rand)->_data_type)
		{
		    delete reinterpret_cast<wipp_rand_t_gaussian_double_t_*>((*rand))->_distribution;
		    delete (*rand)->_generator;
		    delete reinterpret_cast<wipp_rand_t_gaussian_double_t_*>((*rand));
		}
		else if(typeid(float).hash_code() == (*rand)->_data_type)
		{

		    delete reinterpret_cast<wipp_rand_t_gaussian_float_t_*>((*rand))->_distribution;
		    delete (*rand)->_generator;
		    delete reinterpret_cast<wipp_rand_t_gaussian_float_t_*>((*rand));
		}
	    break;
	    default:
	    break;
	}
	*rand = NULL;
    }
}


}
