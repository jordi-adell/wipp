#include <wipp/wippfft.h>

#include <boost/shared_array.hpp>

namespace wipp
{

struct wipp_fft_t_
{
    boost::shared_array<Ipp8u> fftInternalBuffer;
    IppsFFTSpec_R_64f *fftspec;
    int length;
    int order;
};


wipp_fft_t_* wipp_init_fft(size_t length)
{
  if (length <= 0)
    return nullptr;

  int order = (int) log2(length-1) + 1;
  length = 1 << _order;

  _specLength = _length + 2; // This is beacuse the CCs compact form in IPP nees 2 more samples to store the whole spectrum.
  _spectrum.reset(new BaseType[_specLength]);

  wipp_fft_t_ *wipp_fft = new wipp_fft_t_();
  wipp_fft->order = order;
  wipp_fft->length = length;

  ippsFFTInitAlloc_R_64f(&wipp_fft->fftspec, wipp_fft->order, IPP_DIV_FWD_BY_N, ippAlgHintFast);
  int internalBuferSize=0;
  ippsFFTGetBufSize_R_64f(_fftspec, &internalBuferSize);
  wipp_fft->fftInternalBuffer.reset(new Ipp8u[internalBuferSize]);

}


void wipp_destroy_fft(wipp_fft_t *wipp_fft)
{
    free spec
	    free smart pointer
	    free struct
}

wipp_fft_t* wipp_fft(const double *signal, int signallength,
		double *spectrum, int speclength,
		wipp_fft_t *internal_buffer)
{
  if (speclength != _specLength ||  signallength != _length)
    throw DspException("Either the signal or the spectrum buffer lengths are wrong");
  ippsFFTFwd_RToCCS_64f(signal, spectrum, _fftspec, _fftInternalBuffer.get());
}

wipp_fft_t wipp_ifft(const double *spectrum, int speclength,
		 double *signal, int signallength,
		 wipp_fft_t *internal_buffer)
{
  if (speclength != _specLength ||  signallength != _length)
    throw DspException("Either the signal or the spectrum buffer lengths are wrong");
  ippsFFTInv_CCSToR_64f(spectrum, signal, _fftspec, _fftInternalBuffer.get());
}

}
