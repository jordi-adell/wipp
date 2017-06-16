
#ifndef _WIPP_MEL_DEFS_H__
#define _WIPP_MEL_DEFS_H__

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
static const double default_mel_mult64 = 2559;
static const double default_mel_div64  = 700;
static const float default_mel_mult32 = 2559;
static const float  default_mel_div32  = 700;


#endif