#include <wipp/wippfft.h>

#ifdef IPP_FOUND
#include "ipp/ippfft.inl"
#else
#ifdef FFTW_FOUND
#include "fftw3/fftw3.inl"
#endif
#endif

