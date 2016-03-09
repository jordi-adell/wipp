#include <wipp/wippstats.h>

namespace wipp
{

template<typename T>
void sum_core(const T *buffer, size_t length, T* sum)
{
    *sum = 0;
    for (size_t i = 0; i  < length; ++i)
	*sum += buffer[i];
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


void sum(const double *buffer, size_t length, double *sum){ sum_core(buffer, length, sum); }
void sum(const float *buffer, size_t length, float *sum){ sum_core(buffer, length, sum); }
void sum(const int16_t *buffer, size_t length, int16_t *sum){ sum_core(buffer, length, sum); }
void sum(const int32_t *buffer, size_t length, int32_t *sum){ sum_core(buffer, length, sum); }
void sum(const uint16_t *buffer, size_t length, uint16_t *sum){ sum_core(buffer, length, sum); }
void sum(const uint32_t *buffer, size_t length, uint32_t *sum){ sum_core(buffer, length, sum); }

}
