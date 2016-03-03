#include <wipp/wippfft.h>

#ifdef IPP_FOUND
#include "ipp/ippfilter.inl"
#else
#include "default/filter.inl"
#endif

