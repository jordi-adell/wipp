#include <wipp/wippsignal.h>


namespace wipp
{

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

void power_spectrum(const wipp_complex_t *spectrum, double *power, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
	power[i] = spectrum[i].re * spectrum[i].re + spectrum[i].im * spectrum[i].im;
    }

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
