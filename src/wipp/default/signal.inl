#include <wipp/wippsignal.h>


namespace wipp
{


void power_spectrum(const wipp_complex_t *spectrum, double *power, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
	power[i] = spectrum[i].re * spectrum[i].re + spectrum[i].im * spectrum[i].im;
    }

}

void magnitude(const wipp_complex_t *buffer, double *magnitude, size_t length)
{
    for (size_t i = 0; i < length; ++i)
	magnitude[i] = sqrt(buffer[i].re*buffer[i].re + buffer[i].im*buffer[i].im);
}


void ramp(double *buffer, size_t length, double offset, double slope)
{
    for (size_t i = 0; i < length; ++i)
    {
	buffer[i] = slope*i + offset;
    }
}

void triangle(double *buffer, size_t length)
{

    for (size_t i = 0; i < (length/2 + 0.5); ++i)
    {
	buffer[i] = static_cast<double>(i)/(static_cast<double>(length-1)/2);
    }

    for (size_t i = length/2; i < length; ++i)
    {
	buffer[i] = 2 - static_cast<double>(i)/(static_cast<double>(length-1)/2);
    }
}


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
void threshold_lt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }
void threshold_lt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_lt(buffer_in, buffer_out, length, threshold, value); }


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
void threshold_gt(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }
void threshold_gt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_gt(buffer_in, buffer_out, length, threshold, value); }


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
void threshold_let(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }
void threshold_let(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_let(buffer_in, buffer_out, length, threshold, value); }


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
void threshold_get(const double *buffer_in, double *buffer_out, size_t length, double threshold, double value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const float *buffer_in, float *buffer_out, size_t length, float threshold, float value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const int16_t *buffer_in, int16_t *buffer_out, size_t length, int16_t threshold, int16_t value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const int32_t *buffer_in, int32_t *buffer_out, size_t length, int32_t threshold, int32_t value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length, uint16_t threshold, uint16_t value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }
void threshold_get(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length, uint32_t threshold, uint32_t value) { threshold_get(buffer_in, buffer_out, length, threshold, value); }

template<typename T>
struct wipp_circular_buffer_template_t_
{
	T *buffer;
	size_t size;
	size_t occupancy;
	size_t position;
};

struct wipp_circular_buffer_t_
{
	void *buffer;
	size_t size;
	size_t occupancy;
	size_t position;
};

typedef wipp_circular_buffer_template_t_<double> wipp_circular_buffer_double_t_;
typedef wipp_circular_buffer_template_t_<float> wipp_circular_buffer_float_t_;
typedef wipp_circular_buffer_template_t_<int16_t> wipp_circular_buffer_int16_t_t_;
typedef wipp_circular_buffer_template_t_<int32_t> wipp_circular_buffer_int32_t_t_;
typedef wipp_circular_buffer_template_t_<uint16_t> wipp_circular_buffer_uint16_t_t_;
typedef wipp_circular_buffer_template_t_<uint32_t> wipp_circular_buffer_uint32_t_t_;

template <typename T>
void init_cirular_buffer_core(wipp_circular_buffer_template_t_<T> *cb, size_t size, T *init_values, size_t length)
{
    cb = new wipp_circular_buffer_template_t_<T>();
    cb->size = size;
    cb->occupancy = 0;
    cb->position = 0;
    cb->buffer = new T[cb->size];
}

void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, double   *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_double_t_*>(buffer), size, init_values, length); }
void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, float    *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_float_t_*>(buffer), size, init_values, length); }
void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, int16_t  *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_*>(buffer), size, init_values, length); }
void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, int32_t  *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_*>(buffer), size, init_values, length); }
void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, uint16_t *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_*>(buffer), size, init_values, length); }
void init_cirular_buffer(wipp_circular_buffer_t *buffer, size_t size, uint32_t *init_values, size_t length)
{ init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_*>(buffer), size, init_values, length); }


template<typename T>
void cf_read_core(wipp_circular_buffer_template_t_<T> *cb, T *buffer, size_t length, size_t *stored)
{
    size_t i = 0;
    for (;
	 i < length && cb->occupancy > 0;
	 ++i, cb->position=(cb->position+1)%cb->size, --cb->occupancy)
    {
	buffer[i] = cb->buffer[cb->position];
    }
    *stored = i;
}

void cf_read(wipp_circular_buffer_t *cb, double   *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_double_t_*>(cb), buffer, length, stored); }
void cf_read(wipp_circular_buffer_t *cb, float    *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_float_t_*>(cb), buffer, length, stored); }
void cf_read(wipp_circular_buffer_t *cb, int16_t  *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_*>(cb), buffer, length, stored); }
void cf_read(wipp_circular_buffer_t *cb, int32_t  *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_*>(cb), buffer, length, stored); }
void cf_read(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_*>(cb), buffer, length, stored); }
void cf_read(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored)
{ cf_read_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_*>(cb), buffer, length, stored); }


template<typename T>
void cf_write_core(wipp_circular_buffer_template_t_<T> *cb, T *buffer, size_t length, size_t *stored)
{
    size_t i = 0;
    for (size_t k = (cb->position + cb->occupancy)%cb->size;
	 i < length && cb->occupancy < cb->size;
	 ++i, k=(k+1)%cb->size, ++cb->occupancy)
    {
	cb->buffer[k] = buffer[i];
    }
    *stored = i;
}

void cf_write(wipp_circular_buffer_t *cb, double   *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_double_t_*>(cb), buffer, length, stored); }
void cf_write(wipp_circular_buffer_t *cb, float    *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_float_t_*>(cb), buffer, length, stored); }
void cf_write(wipp_circular_buffer_t *cb, int16_t  *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_*>(cb), buffer, length, stored); }
void cf_write(wipp_circular_buffer_t *cb, int32_t  *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_*>(cb), buffer, length, stored); }
void cf_write(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_*>(cb), buffer, length, stored); }
void cf_write(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored)
{ cf_write_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_*>(cb), buffer, length, stored); }


void cf_size(wipp_circular_buffer_t *cb, size_t *size)
{
    *size = cb->size;
}

void cf_occupancy(wipp_circular_buffer_t *cb, size_t *occupancy)
{
    *occupancy = cb->occupancy;
}

void cf_skip(wipp_circular_buffer_t *cb, size_t length, size_t *skipped)
{
    if (length > cb->occupancy) length = cb->occupancy;
    cb->position = (cb->position + length)%cb->size;
    cb->occupancy -= length;
    *skipped = length;
}


// Mel-scale frequency mapping
//
// Parameters are taken from the HTK book.
// note that in the web they use log10 and IPP used Ln.
// http://www.ee.columbia.edu/ln/rosa/doc/HTKBook21/node54.html
//
//                                 linear_freq
//  mel_freq = mult * log_10( 1 + ------------- )
//                                     div
//
static const double default_mult64 = 2559;
static const double default_div64  = 700;
static const float default_mult32 = 2559;
static const float  default_div32  = 700;

template <typename T>
void linear2mel_core(const T *linear, T *mel, size_t length, const T* mult, const T*div)
{
    for (size_t i = 0; i < length; ++i)
	mel[i] = (*mult) * log( 1 + linear[i]/(*div) ) / log(10);
}

void linear2mel(const double *linear, double *mel, size_t length, const double* mult, const double*div) { linear2mel_core(linear, mel, length, mult, div);}
void linear2mel(const double *linear, double *mel, size_t length) { linear2mel(linear, mel, length, &default_mult64, &default_div64);}
void linear2mel(const float *linear, float *mel, size_t length, const float* mult, const float*div) { linear2mel_core(linear, mel, length, mult, div);}
void linear2mel(const float *linear, float *mel, size_t length) { linear2mel(linear, mel, length, &default_mult32, &default_div32);}

template <typename T>
void mel2linear_core(const T *mel, T *linear, size_t length, const T* mult, const T*div)
{
    for (size_t i = 0; i < length; ++i)
	linear[i] = ( exp( mel[i] * log(10) / (*mult) ) - 1 )*(*div);
}

void mel2linear(const double *mel, double *linear, size_t length, const double* mult, const double*div) { mel2linear_core(mel, linear, length, mult, div);}
void mel2linear(const double *mel, double *linear, size_t length) { mel2linear(mel, linear, length, &default_mult64, &default_div64);}
void mel2linear(const float *mel, float *linear, size_t length, const float* mult, const float*div) { mel2linear_core(mel, linear, length, mult, div);}
void mel2linear(const float *mel, float *linear, size_t length) { mel2linear(mel, linear, length, &default_mult32, &default_div32);}


}
