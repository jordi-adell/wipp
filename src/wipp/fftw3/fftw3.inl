#include <wipp/wippfft.h>
#include <fftw3.h>

#include <cstring>

namespace wipp
{

struct wipp_fft_t_
{
	fftw_plan forward_plan;
	double *forward_in;
	fftw_complex *forward_out;

	fftw_plan backward_plan;
	fftw_complex *backward_in;
	double *backward_out;

	size_t length;
};



void init_wipp_fft(wipp_fft_t* fft, size_t length)
{
    fft = new wipp_fft_t_();
    fft->length = length;
    fft->forward_in  = fftw_alloc_real(fft->length);
    fft->forward_out = fftw_alloc_complex(fft->length);
    fft->backward_in  = fftw_alloc_complex(fft->length);
    fft->backward_out = fftw_alloc_real(fft->length);
    fft->forward_plan = fftw_plan_dft_r2c_1d(fft->length, fft->forward_in, fft->forward_out, FFTW_ESTIMATE);
    fft->backward_plan = fftw_plan_dft_c2r_1d(fft->length, fft->backward_in, fft->backward_out, FFTW_ESTIMATE);
}

void delete_wipp_fft(wipp_fft_t *wipp_fft)
{
    fftw_free(wipp_fft->forward_in);
    fftw_free(wipp_fft->forward_out);
    fftw_free(wipp_fft->backward_in);
    fftw_free(wipp_fft->backward_out);
    fftw_destroy_plan(wipp_fft->forward_plan);
    fftw_destroy_plan(wipp_fft->backward_plan);
}

wipp_fft_t* fft(const double *signal, int signallength,
		wipp_complex_t *spectrum, int speclength,
		wipp_fft_t* wipp_fft)
{
    memcpy(reinterpret_cast<void*>(wipp_fft->forward_in),
	   signal, sizeof(double)*wipp_fft->length);

    fftw_execute_dft_r2c(wipp_fft->forward_plan,
			 wipp_fft->forward_in, wipp_fft->forward_out);

    for (size_t i = 0; i < speclength; ++i)
    {
	spectrum[i].re = wipp_fft->forward_out[i][0];
	spectrum[i].im = wipp_fft->forward_out[i][1];
    }
}

wipp_fft_t* ifft(const wipp_complex_t *spectrum, int speclength,
		 double *signal, int signallength,
		 wipp_fft_t* wipp_fft)
{
    for (size_t i = 0; i < wipp_fft->length; ++i)
    {
	wipp_fft->backward_in[i][0] = spectrum[i].re;
	wipp_fft->backward_in[i][1] = spectrum[i].im;
    }
    fftw_execute_dft_c2r(wipp_fft->backward_plan,
			 wipp_fft->backward_in, wipp_fft->backward_out);
    memcpy(signal, reinterpret_cast<void*>(wipp_fft->backward_out), sizeof(double)*signallength);
}

int get_fft_length(wipp_fft_t* wipp_fft)
{
    return wipp_fft->length;
}


}
