/*
 *  ippTest.cpp
 *  Copyright (C) 2016 All Rights Reserved
 *  Created on: 20/02/2016
 *      Author: Jordi Adell (adellj@gmail.com)
 */

#include <gtest/gtest.h>
#include <wipp/wipputils.h>
#include <wipp/wippfilter.h>
#include <wipp/wippsignal.h>
#include <wipp/wippfft.h>
#include <wipp/wippstats.h>
#include <wipp/wipplogger.h>

#ifndef DEBUG_STREAM
#define DEBUG_STREAM(x)
#endif

#include <boost/filesystem.hpp>

#include <limits>
#include <fstream>


namespace wipp
{

// non-exposed fucntion to be tested.
void wipp_sinc(double fmin, double fmax, double *sinc, size_t length);
void wipp_sinc2(double fmin, double fmax, double *sinc, size_t length);

namespace test
{

template<typename T>
void save_buffer(T *buffer, size_t length, const std::string &file_basename)
{
  boost::filesystem::create_directories("./tmp/");
  std::ofstream ofs(std::string("./tmp/") + file_basename + ".txt");
  for (size_t i = 0; i < length; ++i)
    ofs << buffer[i] << std::endl;
}

TEST(wippTest, wippCopyTest)
{
    const int len = 4;
    double dmin = std::numeric_limits<double>::min();
    double dmax = std::numeric_limits<double>::max();

    float fmin = std::numeric_limits<float>::min();
    float fmax = std::numeric_limits<float>::max();

    short int smin = std::numeric_limits<short int>::min();
    short int smax = std::numeric_limits<short int>::max();

    unsigned short int usmin = std::numeric_limits<unsigned short int>::min();
    unsigned short int usmax = std::numeric_limits<unsigned short int>::max();

    int imin = std::numeric_limits<int>::min();
    int imax = std::numeric_limits<int>::max();

    DEBUG_STREAM(" min: " << fmin << " max: " << fmax << " : " << 2*(fmin/3) + fmax/3 << " " << 2*fmin/3);

    double inDbuffer[len] = {dmin, 2*(dmin/3) + dmax/3, dmin + 2*(dmax/3), dmax};
    float  inFbuffer[len] = {fmin, 2*(fmin/3) + fmax/3, fmin/3 + 2*(fmax/3), fmax};
    short  inSbuffer[len] = {smin, static_cast<short>(2*(smin/3) + smax/3), static_cast<short>(smin/3 + 2*(smax/3)), smax};
    int inIbuffer[len] =  {smin, static_cast<int> (2*(imin/3) + imax/3), static_cast<int> (imin/3 + 2*(imax/3)), imax};
    unsigned short inUSbuffer[len] = {usmin, static_cast<unsigned short int> (2*(usmin/3) + usmax/3), static_cast<unsigned short int> (usmin/3 + 2*(usmax/3)), usmax};

    double oDbuffer[len];
    float  oFbuffer[len];
    short  oSbuffer[len];
    int   oIbuffer[len];
    unsigned short oUSbuffer[len];

    // Check equal resolution
    copyBuffer(inDbuffer, oDbuffer, len);
    copyBuffer(inFbuffer, oFbuffer, len);
    copyBuffer(inSbuffer, oSbuffer, len);
    copyBuffer(inIbuffer, oIbuffer, len);
    copyBuffer(inUSbuffer, oUSbuffer, len);

    for (int i = 0; i<len; ++i)
    {
	DEBUG_STREAM("D: " << inDbuffer[i] << " D: " << oDbuffer[i]);
	EXPECT_EQ(inDbuffer[i], oDbuffer[i]);
	DEBUG_STREAM("F: " << inFbuffer[i] << " F: " << oFbuffer[i]);
	EXPECT_EQ(inFbuffer[i], oFbuffer[i]);
	DEBUG_STREAM("S: " << inSbuffer[i] << " S: " << oSbuffer[i]);
	EXPECT_EQ(inSbuffer[i], oSbuffer[i]);
	DEBUG_STREAM("I: " << inIbuffer[i] << " I: " << oIbuffer[i]);
	EXPECT_EQ(inIbuffer[i], oIbuffer[i]);
	DEBUG_STREAM("US: " << inIbuffer[i] << " US: " << oIbuffer[i]);
	EXPECT_EQ(inUSbuffer[i], oUSbuffer[i]);
    }

    // from Low to High resolution

    copyBuffer(inSbuffer, oFbuffer, len);
    copyBuffer(inSbuffer, oDbuffer, len);
    for (int i = 0; i<len; ++i)
    {
	DEBUG_STREAM("S: " << inSbuffer[i] << " F: " << oFbuffer[i]);
	EXPECT_EQ(inSbuffer[i], oFbuffer[i]);
	DEBUG_STREAM("S: " << inSbuffer[i] << " D: " << oDbuffer[i]);
	EXPECT_EQ(inSbuffer[i], oDbuffer[i]);
    }
    copyBuffer(inIbuffer, oFbuffer, len);
    copyBuffer(inIbuffer, oDbuffer, len);
    for (int i = 0; i<len; ++i)
    {
	DEBUG_STREAM("I: " << inIbuffer[i] << " F: " << oFbuffer[i]);
	EXPECT_EQ(inIbuffer[i], oFbuffer[i]);
	DEBUG_STREAM("I: " << inIbuffer[i] << " D: " << oDbuffer[i]);
	EXPECT_EQ(inIbuffer[i], oDbuffer[i]);
    }
    copyBuffer(inUSbuffer, oFbuffer, len);
    copyBuffer(inUSbuffer, oDbuffer, len);
    for (int i = 0; i<len; ++i)
    {
	DEBUG_STREAM("US: " << inUSbuffer[i] << " F: " << oFbuffer[i]);
	EXPECT_EQ(inUSbuffer[i], oFbuffer[i]);
	DEBUG_STREAM("US: " << inUSbuffer[i] << " D: " << oDbuffer[i]);
	EXPECT_EQ(inUSbuffer[i], oDbuffer[i]);
    }

}


TEST(sqrTest, sqrt_sqr)
{
  size_t length = 1000;
  double frame[length];
  double sqrt_frame[length];
  double sqr_frame[length];
  wipp::wipp_rand_t *rand;
  wipp::init_rand_gaussian(&rand, 100, 10);
  wipp::rand(rand, frame, length);
  wipp::threshold_get(frame, length, 0, 0);

  wipp::sqrt(frame, sqrt_frame, length);
  wipp::sqr(frame, sqr_frame, length);

  for (size_t i = 0; i < length; ++i)
    EXPECT_EQ(sqrt_frame[i]*sqrt_frame[i], frame[i]);
  for (size_t i = 0; i < length; ++i)
    EXPECT_EQ(sqr_frame[i], frame[i]*frame[i]);


}

TEST(sum, complex)
{
  int length = 1 << 10;
  wipp_complex_t signal[length];
  wipp_complex_t value, sum_value;

  value.re = 1;
  value.im = 1;

  for (int i = 0; i < length; ++i)
  {
    signal[i] = value;
  }

  wipp::sum(signal, length, &sum_value);
  
  EXPECT_EQ(length, sum_value.re);
  EXPECT_EQ(length, sum_value.im);

}


TEST(utils, sub)
{

  size_t length=7;
  double a[]={1, 2, 3, 4, 3, 2, 1};
  double b[]={0, 1, 2, 3, 2, 1, 0};

  wipp::sub(b, a, length);

  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_EQ(a[i], 1);
  }

}


TEST(utils, minmax)
{
  size_t length = 14;
  double data[] = {1, 2, 3, 4, 5, -200, 6, 7, 8, 9, 9.3, -4, -5 , 6, -7};
  size_t idx;
  double max, min;

  wipp::maxidx(data, length, &max, &idx);
  EXPECT_EQ(max, 9.3);
  EXPECT_EQ(idx, 10);

  wipp::minidx(data, length, &min, &idx);
  EXPECT_EQ(min, -200);
  EXPECT_EQ(idx, 5);
}



TEST(utils, threshold)
{

  size_t length = 20;
  double data[length];
  double filtered[length];

  wipp::wipp_rand_t *rand;
  wipp::init_rand_gaussian(&rand, 0, 1);

  wipp::rand(rand, data, length);

  wipp::threshold_lt_gt(data, filtered, length, 0, 0, 1, 1);

  for (size_t i = 0; i < length; ++i)
  {
    if (data[i] < 0)
    {
      EXPECT_EQ(filtered[i], 0);
    }
    else if (data[i] > 1)
    {
      EXPECT_EQ(filtered[i], 1);
    }
    else
    {
      EXPECT_EQ(filtered[i], data[i]);
    }
  }

}



TEST(div, complex)
{
  int length = 2;
  wipp_complex_t a[length];
  wipp_complex_t b[length];
  wipp_complex_t c[length];
  wipp_complex_t ref[length];


  a[0].re = 1;
  a[0].im = 2;
  a[1].re = 3;
  a[1].im = -4;

  b[0].re = 5;
  b[0].im = 6;
  b[1].re = 7;
  b[1].im = -8;

  double denom = 5*5 + (6)*(6);
  ref[0].re = (1*5 + 2*(6)) / denom;
  ref[0].im = (2*5 - 1*(6)) / denom;

  denom = 7*7 + (-8)*(-8);
  ref[1].re = (3*7 + (-4)*(-8)) / denom;
  ref[1].im = ((-4)*7 - 3*(-8)) / denom;

  // (b + bij) * (b - bij)
  // (b*b - b*bij + bi*bj + bi*bi

  // (a + aij) / (b + bij)
  // (a + aij) * (b - bij) / (b*b + bi*bi)
  // (a*b - a*bij + ai*bj + aibi) / (b*b + bi*bi)
  // (a*b + aibi + (ai*b - abi)j) / (b*b + bi*bi)

  wipp::div(b, a, c, length);

  for (int i = 0; i < length; ++i)
  {
    EXPECT_EQ(ref[i].re, c[i].re);
    EXPECT_EQ(ref[i].im, c[i].im);
  }

}

TEST (threshold, lt_gt_let_get)
{

  size_t length = 1000;
  double frame[length];
  double out_frame[length];
  wipp::wipp_rand_t *rand;
  wipp::init_rand_gaussian(&rand, 0.0F, 1000.0F);
  wipp::rand(rand, frame, length);

  wipp::threshold_lt(frame, out_frame, length, 0.0, -1000.0F);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] > 0 || out_frame[i] == -1000);
    if (frame[i] >= 0)
      EXPECT_GE(out_frame[i], 0);
    else
      EXPECT_EQ(out_frame[i], -1000);
  }

  wipp::threshold_gt(frame, out_frame, length, 0, 1000);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] < 0 || out_frame[i] == 1000);
    if (frame[i] <= 0)
      EXPECT_LE(out_frame[i], 0);
    else
      EXPECT_EQ(out_frame[i], 1000);
  }

  wipp::threshold_let(frame, out_frame, length, 0.0, -1000.0F);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] > 0 || out_frame[i] == -1000);
    if (frame[i] > 0)
      EXPECT_GE(out_frame[i], 0);
    else
      EXPECT_EQ(out_frame[i], -1000);
  }

  wipp::threshold_get(frame, out_frame, length, 0, 1000);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] < 0 || out_frame[i] == 1000);
    if (frame[i] < 0)
      EXPECT_LE(out_frame[i], 0);
    else
      EXPECT_EQ(out_frame[i], 1000);
  }

  wipp::threshold_lt_gt(frame, out_frame, length, 0, -1, 10, 20);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] >= 0 && out_frame[i] < 10  || out_frame[i] == -1 || out_frame[i] == 20 );
    if (frame[i] <= 0)
      EXPECT_LE(out_frame[i], -1);
    else if (frame[i] >= 10)
      EXPECT_EQ(out_frame[i], 20);
  }

  wipp::threshold_let_get(frame, out_frame, length, 0, -1, 10, 20);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_TRUE(out_frame[i] >= 0 && out_frame[i] < 10  || out_frame[i] == -1 || out_frame[i] == 20 );
    if (frame[i] < 0)
      EXPECT_LE(out_frame[i], -1);
    else if (frame[i] > 10)
      EXPECT_EQ(out_frame[i], 20);
  }


}

TEST(iirTest, init_delete)
{

  wipp::wipp_iir_filter_t *iir;
  static const int n = 6;
  double b_coefs[n]={2, -2, 1, 1 , -2, 2};
  double a_coefs[n]={1, 1, 1, 1 , 1, 1};

  wipp::init_iir(&iir, a_coefs, n, b_coefs, n);

  EXPECT_FALSE(iir == NULL);

  wipp::delete_iir(&iir);

  EXPECT_TRUE(iir == NULL);

  wipp::delete_iir(&iir);

}

TEST(iirTest, filter)
{
    wipp::wipp_iir_filter_t *iir;
    static const int n = 2;
    static const int length = 10;
    double b_coefs[n] = {1, 0.97};
    double a_coefs[n] = {1, 0};

    double signal[length] = {1000, 1000, 1000, 1000, 0, 0, 0, 0, 0, 0};
    double reference[length] = {1.0000e3, 0.0300e3, 0.9709e3, 0.05822699e3, -0.05648019e3, 0.0547857e3, -0.0531422e3, 0.0515479e3, -0.05000150061e3, 0.04850146e3};
    double filtered[length];

    wipp::init_iir(&iir, a_coefs, n, b_coefs, n);

    EXPECT_FALSE(iir == nullptr);

    wipp::iir_filter(iir, signal, filtered, length);

    for (int i = 0; i < length; ++i)
    {
	EXPECT_NEAR(reference[i], filtered[i], 1e-4);
    }
}

TEST(firTest, init_delete)
{

  for (float N = 1; N < 100000; N = N*1.05)
  {
    size_t n = N;
    DEBUG_STREAM("order: " << n);

    wipp::wipp_fir_filter_t *fir;
    double coefs[n];

    for (size_t c = 0; c < n; ++c)
    {
      coefs[c] = std::rand();
    }

    wipp::init_fir(&fir, coefs, n);
    EXPECT_FALSE(fir == NULL);

    wipp::delete_fir(&fir);

    EXPECT_TRUE(fir == NULL);

    wipp::delete_fir(&fir);
  }
}

TEST(firTest, filter)
{

  for (int n_coefs = 64; n_coefs < 512; n_coefs += 64)
  {
    DEBUG_STREAM("N_COEFS: " << n_coefs);
    int length = 3*n_coefs;
    wipp::wipp_fir_filter_t *filter;
    double lf = 0.1;
    double hf = 0.3;
    double coefs[length];

    double signal[length];
    double filtered[length];
    double signal_power, filtered_power;

    wipp::fir_coefs(lf, hf, coefs, n_coefs, wipp::wippHANN);

    wipp::init_fir(&filter, coefs, n_coefs);

    for (double freq = 0.01; freq < 0.49; freq += 0.005)
    {
      for (size_t i = 0; i < length; ++i)
      {
	signal[i] = 2*cos(2*M_PI*freq*i);
      }

      wipp::power(signal, filtered, length);
      wipp::sum(filtered, length, &signal_power);
      signal_power /= length;
      signal_power= 10*log10(signal_power);

      EXPECT_NEAR(signal_power, 3, 0.2);

      wipp::fir_filter(filter, signal, filtered, length);

      wipp::power(filtered, length);
      wipp::sum(filtered, length, &filtered_power);
      filtered_power /= length;
      filtered_power = 10*log10(filtered_power);

      double gain = filtered_power - signal_power;
      INFO_STREAM("Filtered Power " << freq << ": " << gain << " dB");

      if (freq < lf*0.9)
	EXPECT_LT(gain, -15);
      else if (lf*1.1 < freq && freq < hf*0.9)
	EXPECT_NEAR(0, gain, 5);
      else if (freq > hf*1.1)
	EXPECT_LT(gain, -15);

    }
  }
}

TEST(firTest, coefs)
{
  size_t length = 2048;
  double coefs[length];
  double fir_coefs[length];
  wipp::fir_coefs(0.1, 0.3, coefs, length, wippHANN);

  wipp::wipp_fir_filter_t *fir;
  wipp::init_fir(&fir, coefs, length);

  wipp::fir_get_coefs(fir, fir_coefs, length);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_EQ(coefs[i], fir_coefs[i]);
  }

}


TEST(firTest, sinc)
{
  double fmin=0.1;
  double fmax=0.3;
  int length = 2048;
  double frame[length];
  double spectrum[length+2];
  double magnitude[1024];
  wipp_sinc(fmin, fmax, frame, length);

  wipp::wipp_fft_t *fft;
  wipp::init_fft(&fft, length);
  wipp::fft(frame, spectrum, fft);
  wipp::magnitude(reinterpret_cast<wipp_complex_t*>(spectrum), magnitude, length/2);
  wipp::power(magnitude, length/2);
  std::ofstream ofs("datat.txt");

  for (int i = 0; i < length/2; ++i)
  {

      ofs << magnitude[i] << std::endl;
      double f = i*1.0F/length;
      DEBUG_STREAM("i: " << i << ", f: " << f << ", FFT abs: " << magnitude[i]);
      if (f < fmin)
	  EXPECT_LT(magnitude[i], 1);
      else if (f > 1.05*fmin && f < fmax*0.99)
	  EXPECT_NEAR(1, magnitude[i], 0.05);
      else if (f > fmax)
	  EXPECT_LT(magnitude[i], 1);
  }

  wipp::delete_fft(&fft);
}

TEST(firTest, sinc2)
{
  double fmin=0.1;
  double fmax=0.3;
  int length = 2048;
  double frame[length];
  double spectrum[length+2];
  double magnitude[1024];

  wipp_sinc2(fmin, fmax, frame, length);

  //  window(frame, length, wipp::wippHANN);

  wipp::wipp_fft_t *fft;
  wipp::init_fft(&fft, length);
  wipp::fft(frame, spectrum, fft);
  wipp::magnitude(reinterpret_cast<wipp_complex_t*>(spectrum), magnitude, length/2);
  wipp::power(magnitude, length/2);

  float prev = std::numeric_limits<float>::min();
  for (int i = 0; i < length/2; ++i)
  {
      double f = i*1.0F/length;
      DEBUG_STREAM("i: " << i << ", f: " << f << ", FFT abs: " << magnitude[i]);
      if (f < fmin)
	EXPECT_LT(magnitude[i], 1);
      else if (f > 1.05*fmin && f < (fmax+fmin)*0.99/2)
	EXPECT_GT(magnitude[i], prev);
      else if (f > 1.05*(fmax+fmin)/2 && f < 0.99*fmax)
	EXPECT_LT(magnitude[i], prev);
      else
	EXPECT_LT(magnitude[i], 1);
      prev = magnitude[i];
  }

  save_buffer(magnitude, length/2, "data");
  save_buffer(frame, length/2, "datat");

  wipp::delete_fft(&fft);
}


TEST(firTest, tone_filter)
{

  int length = 10000;
  double signal[length];
  double filtered[length];
  double phase = 0;
  int fir_length = 1024;
  double coefs[fir_length];
  double fmin, fmax;
  fmin = 0.1;
  fmax = 0.35;

  double delta = 0.01;
  double delta_bw = 0.07;

  for (double fmin = 0.2; fmin < 0.5; fmin = fmin + delta_bw)
  {
    for (double fmax = fmin + delta; fmax < 0.5; fmax = fmax + delta_bw)
    {
      wipp::wipp_fir_filter_t *fir;
      wipp::wipp_sinc2(fmin, fmax, coefs, fir_length);
      wipp::init_fir(&fir, coefs, fir_length);

      double prevp = -1000;
      for (double freq = 0; freq < 0.5; freq = freq + delta)
      {
	wipp::tone(signal,length, 5, freq, phase);
	wipp::fir_filter(fir, signal, filtered, length);

	double spower, fpower;
	wipp::power(signal, length);
	wipp::mean(signal, length, &spower);
	wipp::power(filtered, length);
	wipp::mean(filtered, length, &fpower);

	if (fpower < 0.001) fpower = 0;
	DEBUG_STREAM("BW: " << std::setprecision(2) <<  fmin << "-" << fmax << "; F: " << freq << ", SP: "<< spower << ", FP: " << fpower);

	if (fmax - fmin > 0.2)
	{
	  if (freq < fmin)
	    EXPECT_LE(fpower, 3);
	  else if (freq < (fmax+fmin)*0.985/2)
	  {
	    EXPECT_GE(fpower, prevp);
	  }
	  else if (freq < (fmax+fmin)*1.015/2)
	  {
	    EXPECT_NEAR(fpower, prevp, 2.2);
	  }
	  else if(freq <= fmax)
	  {
	    EXPECT_LE(fpower, prevp);
	  }
	  else
	    EXPECT_LE(fpower, 3);
	}

	prevp = fpower;

      }
    }
  }



}



TEST(circularBufferTest, init_delete)
{
  wipp::wipp_circular_buffer_t *cf;
  wipp::init_cirular_buffer<double>(&cf, 1024);

  EXPECT_FALSE(cf == NULL);

  wipp::delete_circular_buffer(&cf);

  EXPECT_TRUE(cf == NULL);

  wipp::delete_circular_buffer(&cf);

}

TEST(circularBufferTest, occupancy)
{

  wipp::wipp_circular_buffer_t *cf;
  const size_t cf_length = 1024;
  const size_t step = 131;
  size_t stored, occupancy, free, data_position, output_position;
  occupancy = free = data_position = output_position = 0;

  double data[2*cf_length];
  double output[2*cf_length];

  wipp::set(1, data, cf_length);

  wipp::init_cirular_buffer<double>(&cf, cf_length);
  wipp::cf_write(cf, data, cf_length/2, &stored);
  wipp::cf_occupancy(cf, &occupancy);
  EXPECT_EQ(cf_length/2, stored);
  EXPECT_EQ(cf_length/2, occupancy);
  wipp::delete_circular_buffer(&cf);

  wipp::init_cirular_buffer<double>(&cf, cf_length);
  wipp::cf_write(cf, data, cf_length, &stored);
  wipp::cf_occupancy(cf, &occupancy);
  EXPECT_EQ(cf_length, stored);
  EXPECT_EQ(cf_length, occupancy);
  wipp::delete_circular_buffer(&cf);

  wipp::init_cirular_buffer<double>(&cf, cf_length);
  wipp::cf_write(cf, data, cf_length + cf_length/2, &stored);
  wipp::cf_occupancy(cf, &occupancy);
  EXPECT_EQ(cf_length, stored);
  EXPECT_EQ(cf_length, occupancy);
  wipp::cf_write(cf, data, cf_length + cf_length/2, &stored);
  wipp::cf_occupancy(cf, &occupancy);
  EXPECT_EQ(0, stored);
  EXPECT_EQ(cf_length, occupancy);
  wipp::delete_circular_buffer(&cf);
  
}

TEST(circularBufferTest, write_read)
{

  wipp::wipp_circular_buffer_t *cf;
  const size_t cf_length = 1024;
  const size_t step = 131;
  size_t stored;
  size_t occupancy = 0;
  size_t free;
  size_t data_position = 0;
  size_t output_position = 0;
  wipp::init_cirular_buffer<double>(&cf, cf_length);
  double data[2*cf_length];
  double output[2*cf_length];

  wipp::cf_read(cf, output, step, &stored);

  EXPECT_TRUE(stored == 0);

  for (size_t i = 0; i < 2*cf_length; ++i)
    data[i] = 0;

  wipp::cf_free(cf, &free);

  for (data_position = 0; data_position < 2*cf_length && free > 0; )
  {
    wipp::cf_free(cf, &free);
    wipp::cf_write(cf,&data[data_position], step, &stored);
    EXPECT_TRUE(stored == std::min(step, free));
    if (data_position < cf_length - step)
    {
      EXPECT_EQ(stored, step);
    }

    data_position += stored;

    size_t new_occ = occupancy + stored;
    wipp::cf_occupancy(cf, &occupancy);
    EXPECT_EQ(occupancy, new_occ);

    DEBUG_STREAM("Free: " << free << " stored: " << stored);

    if (stored == 0)
    {
      EXPECT_EQ(data_position, cf_length);
    }
    else if (stored < step)
    {
      size_t remaining = cf_length%step;
      EXPECT_EQ(stored, remaining);
    }
  }

  wipp::cf_occupancy(cf, &occupancy);

  EXPECT_EQ(occupancy, cf_length);
  EXPECT_EQ(data_position, cf_length);

  for (stored = 0; data_position < 2*cf_length; )
  {
    size_t read_data;
    wipp::cf_read(cf, &output[output_position], step, &read_data);
    output_position += read_data;

    EXPECT_EQ(read_data, step);

    size_t new_occ = occupancy - read_data;
    wipp::cf_occupancy(cf, &occupancy);
    EXPECT_EQ(occupancy, new_occ);

    if (step <  2*cf_length - data_position)
    {
      wipp::cf_write(cf, &data[data_position], step, &stored);
      EXPECT_EQ(stored, step);
      EXPECT_EQ(stored, read_data);
    }
    else
    {
      wipp::cf_write(cf, &data[data_position], 2*cf_length - data_position, &stored);
      EXPECT_EQ(stored, 2*cf_length - data_position);
    }

    data_position += stored;

    new_occ = occupancy + stored;
    wipp::cf_occupancy(cf, &occupancy);
    EXPECT_EQ(occupancy, new_occ);
  }

  EXPECT_EQ(data_position, 2*cf_length);
  EXPECT_EQ(occupancy, cf_length - step + stored);

  do
  {
    size_t remaining_space = 2*cf_length - output_position;
    if (remaining_space < step)
      wipp::cf_read(cf, &output[output_position], remaining_space, &stored);
    else
      wipp::cf_read(cf, &output[output_position], step, &stored);

    output_position += stored;
  } while (stored > 0);

  wipp::cf_occupancy(cf, &occupancy);
  EXPECT_EQ(occupancy, 0);

  EXPECT_EQ(output_position, 2*cf_length);

  double sum;
  wipp::sub(data, output, 2*cf_length);
  wipp::abs(output, 2*cf_length);
  wipp::sum(output, 2*cf_length, &sum);
  EXPECT_EQ(sum, 0);

}


TEST(fftTest, init_delete)
{

  for (int i = 0; i < 15; ++i)
  {
    DEBUG_STREAM("order: " << (1 << i));
    wipp::wipp_fft_t *fft;
    wipp::init_fft(&fft, 1 << i);

    EXPECT_FALSE(fft == NULL);

    wipp::delete_fft(&fft);

    EXPECT_TRUE(fft == NULL);

    wipp::delete_fft(&fft);
  }


  for (int i = 1; i < 512; ++i)
  {
    if (i % 100 == 0)
      DEBUG_STREAM("up to order: " << i);
    wipp::wipp_fft_t *fft;
    wipp::init_fft(&fft, i);

    EXPECT_FALSE(fft == NULL);

    wipp::delete_fft(&fft);

    EXPECT_TRUE(fft == NULL);

    wipp::delete_fft(&fft);
  }

}

TEST(conj, basic)
{
  int length = 4;
  wipp::wipp_complex_t signal[length];
  wipp::wipp_complex_t conj[length];
  signal[0].re = 1; //
  signal[0].im = -2;
  signal[1].re = 3; //
  signal[1].im = 4;
  signal[2].re = 5; //
  signal[2].im = -6;
  signal[3].re = 7; //
  signal[3].im = 8;

  wipp::conj(signal, conj, length);

  for  (int i = 0; i < length; ++i)
  {
    EXPECT_EQ(signal[i].re, conj[i].re);
    EXPECT_EQ(-signal[i].im, conj[i].im);
  }

  wipp::conjFlip(signal, conj, length);

  for (int i = 1; i <= length; ++i)
  {
    EXPECT_EQ( signal[i-1].re, conj[length - i].re);
    EXPECT_EQ(-signal[i-1].im, conj[length - i].im);
  }


  wipp::conjFlip(signal, signal, length);

  for (int i = 0; i < length; ++i)
  {
    EXPECT_EQ(signal[i].re, conj[i].re);
    EXPECT_EQ(signal[i].im, conj[i].im);
  }

}



void fftTestTransform(double freq, int fft_length, const std::vector<double> &fft_ref)
{
  wipp::wipp_fft_t *fft;
  wipp::init_fft(&fft, fft_length);

  double signal[fft_length];
  double isignal[fft_length];
  double signal_fft[fft_length+2];

  for (size_t i = 0; i < fft_length; ++i)
  {
    signal[i] = sin(2*M_PI*freq*i);
  }

  //  save_buffer(signal, fft_length, "signal");

  wipp::fft(signal, signal_fft, fft);

  for (size_t i = 0; i < fft_length; ++i)
  {
//    std::cout << i << " " << signal_fft[i] << " " << fft_ref[i] << std::endl;
    EXPECT_NEAR(signal_fft[i], fft_ref[i], 1e-4);
  }

  EXPECT_DOUBLE_EQ(signal_fft[1], 0);
  EXPECT_DOUBLE_EQ(signal_fft[fft_length + 1], 0);

//  save_buffer(signal_fft, fft_length, "signal_fft");

  wipp::ifft(signal_fft, isignal, fft);

  for (size_t i = 0; i < fft_length; ++i)
  {
    EXPECT_NEAR(signal[i], isignal[i]/fft_length, 1e-12);
  }

  //  save_buffer(isignal, fft_length, "isignal");

  wipp::delete_fft(&fft);

}

TEST(fftTest, transform)
{

  int fft_length = 256;

  std::vector<double> fft_ref = {3.8167, 0.0000, 3.8262, -0.0125, 3.8549, -0.0251, 3.9036, -0.0381,
				3.9739, -0.0517, 4.0679, -0.0660, 4.1887, -0.0815, 4.3408, -0.0983,
				4.5302, -0.1170, 4.7651, -0.1381, 5.0572, -0.1625, 5.4233, -0.1911,
				5.8884, -0.2256, 6.4908, -0.2685, 7.2928, -0.3236, 8.4024, -0.3979,
				10.0241, -0.5041, 12.5974, -0.6700, 17.2715, -0.9679, 28.3015, -1.6655,
				85.4030, -5.2614, -77.2135, 4.9662, -25.8917, 1.7341, -15.3188, 1.0659,
				-10.7648, 0.7765, -8.2343, 0.6145, -6.6271, 0.5107, -5.5180, 0.4383,
				-4.7081, 0.3849, -4.0917, 0.3437, -3.6078, 0.3109, -3.2184, 0.2842,
				-2.8987, 0.2619, -2.6319, 0.2430, -2.4063, 0.2268, -2.2132, 0.2127,
				-2.0462, 0.2002, -1.9007, 0.1892, -1.7727, 0.1794, -1.6595, 0.1705,
				-1.5588, 0.1625, -1.4686, 0.1551, -1.3875, 0.1484, -1.3142, 0.1422,
				-1.2478, 0.1365, -1.1872, 0.1312, -1.1320, 0.1262, -1.0813, 0.1216,
				-1.0348, 0.1173, -0.9919, 0.1132, -0.9522, 0.1094, -0.9156, 0.1058,
				-0.8815, 0.1023, -0.8498, 0.0991, -0.8203, 0.0960, -0.7928, 0.0930,
				-0.7671, 0.0902, -0.7430, 0.0875, -0.7204, 0.0850, -0.6992, 0.0825,
				-0.6792, 0.0801, -0.6604, 0.0779, -0.6427, 0.0757, -0.6260, 0.0736,
				-0.6103, 0.0715, -0.5953, 0.0695, -0.5812, 0.0676, -0.5678, 0.0658,
				-0.5552, 0.0640, -0.5431, 0.0623, -0.5317, 0.0606, -0.5209, 0.0590,
				-0.5106, 0.0574, -0.5007, 0.0558, -0.4914, 0.0543, -0.4825, 0.0528,
				-0.4740, 0.0514, -0.4659, 0.0500, -0.4582, 0.0486, -0.4508, 0.0473,
				-0.4438, 0.0460, -0.4371, 0.0447, -0.4307, 0.0435, -0.4246, 0.0422,
				-0.4187, 0.0410, -0.4131, 0.0398, -0.4078, 0.0387, -0.4027, 0.0375,
				-0.3978, 0.0364, -0.3931, 0.0353, -0.3887, 0.0342, -0.3844, 0.0331,
				-0.3803, 0.0321, -0.3764, 0.0310, -0.3727, 0.0300, -0.3691, 0.0290,
				-0.3657, 0.0280, -0.3625, 0.0270, -0.3594, 0.0260, -0.3564, 0.0251,
				-0.3536, 0.0241, -0.3509, 0.0232, -0.3484, 0.0222, -0.3460, 0.0213,
				-0.3437, 0.0204, -0.3415, 0.0195, -0.3394, 0.0186, -0.3374, 0.0177,
				-0.3356, 0.0168, -0.3338, 0.0159, -0.3322, 0.0150, -0.3307, 0.0142,
				-0.3292, 0.0133, -0.3279, 0.0125, -0.3266, 0.0116, -0.3255, 0.0108,
				-0.3244, 0.0099, -0.3234, 0.0091, -0.3226, 0.0082, -0.3218, 0.0074,
				-0.3211, 0.0066, -0.3204, 0.0058, -0.3199, 0.0049, -0.3194, 0.0041,
				-0.3191, 0.0033, -0.3188, 0.0025, -0.3186, 0.0016, -0.3185, 0.0008,
				-0.3184, 0.0000};

  fftTestTransform(0.08, fft_length, fft_ref);

  fft_ref = { -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000,
	      -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000,
	      -0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000, -0.0000,
	       0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000,  0.0000,  0.0000, -0.0000, -0.0000, -0.0000,
	      -0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,
	      -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,
	       0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,
	       0.0000,  0.0000, -0.0000, -128.00,  0.0000, -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000,
	       0.0000, -0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,
	       0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000,
	      -0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000,
	      -0.0000, -0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000,
	      -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,
	       0.0000, -0.0000,  0.0000,  0.0000, -0.0000, -0.0000,  0.0000, -0.0000,  0.0000, -0.0000,  0.0000,  0.0000,  0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000,
	       0.0000, -0.0000,  0.0000,  0.0000, -0.0000,  0.0000};





  fftTestTransform(0.25, fft_length, fft_ref);

}



TEST(randTest, init_delete)
{
  wipp::wipp_rand_t *rand;
  wipp::init_rand_gaussian(&rand, 0, 1);

  EXPECT_FALSE(rand == NULL);

  wipp::delete_rand(&rand);

  EXPECT_TRUE(rand == NULL);

  wipp::delete_rand(&rand);

}





TEST(testWindowing, hanning)
{

  double hanning16[16]={0,0.0432,0.1654,0.3455,0.5523,0.7500,0.9045,0.9891,0.9891,0.9045,0.7500,0.5523,0.3455,0.1654,0.0432,0};
  double hanning32[32]={0,0.0102,0.0405,0.0896,0.1555,0.2355,0.3263,0.4243,0.5253,0.6253,0.7202,0.8061,0.8794,0.9372,0.9771,0.9974,0.9974,0.9771,0.9372,0.8794,0.8061,0.7202,0.6253,0.5253,0.4243,0.3263,0.2355,0.1555,0.0896,0.0405,0.0102,0};

  for (size_t n=16; n <= 2048; n=n*2)
  {
    DEBUG_STREAM("Hanning window length " << n);
    double frame[n];
    wipp::set(1, frame, n);
    wipp::window(frame, n, wipp::wippHANN);

    for (size_t i = 0; i < n; ++i)
    {
      if (n == 16)
	EXPECT_LT(fabs(frame[i] - hanning16[i]), 5e-5);
      else if (n == 32)
	EXPECT_LT(fabs(frame[i] - hanning32[i]), 5e-5);
      else
	EXPECT_EQ((1-cos(2*M_PI*i/(n-1)))/2, frame[i]);
    }

  }

}


TEST(testSet, zeros)
{
  int length = 1024;
  double buffer[length];

 wipp::setZeros(buffer, length);

 for (size_t i = 0; i < length; ++i)
 {
   EXPECT_EQ(buffer[i],0);
 }
}

TEST(testSet, value)
{
  int length = 1024;
  double buffer[length];

  wipp::set(1, buffer, length);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_EQ(buffer[i],1);
  }

}

TEST(testWindowing, ola)
{
  const int n_windows = 100;
  for (size_t window_size = 1024; window_size < 4096; window_size = window_size + 64)
  {
    size_t window_shift = window_size/2;
    size_t ola_length = window_shift*(n_windows+1);

    DEBUG_STREAM("Window size: " << window_size << ", ola length:" << ola_length << ", window_shift: " << window_shift);

    double frame[window_size];
    double ola[ola_length];

    wipp::set(1,frame, window_size);
    wipp::setZeros(ola, ola_length);

    wipp::window(frame, window_size, wipp::wippHANN);

    for (int n = 0; n < n_windows; ++n)
      wipp::add(frame, &ola[window_shift*n], window_size);

    for (size_t i = window_shift; i < ola_length - window_shift; ++i)
    {
      EXPECT_LT(fabs(ola[i] - 1), 2e-3);
    }

  }

}


TEST(correlation, cross_corr)
{

  double b1[] = {0, 0.2, 0.5, 0.9, 1, 0.9, 0.5, 0.2, 0};
  double b2[] = {1, 1, 1, 1};
  double c[10];
  double c_res[10]  = {1.6, 0.7, 0.2, 0, 0, 0, 0, 0, 0, 0};
  double c_2res[10] = {1.6, 2.6, 3.3, 3.3, 2.6, 1.6, 0.7, 0.2, 0, 0};

  wipp::cross_corr(b1, 9, b2, 4, c, 10, 0);

  for (int i = 0; i < 10; ++i)
  {
    EXPECT_DOUBLE_EQ(c_res[i], c[i]);
  }

  wipp::cross_corr(b2, 4, b1, 9, c, 10, 0);

  for (int i = 0; i < 10; ++i)
  {
    EXPECT_DOUBLE_EQ(c_2res[i], c[i]);
  }

}




TEST(testComplex,reinterpret)
{

  size_t complex_length = 1024;
  wipp::wipp_complex_t complex[complex_length];
  double real[2*complex_length];

  for (size_t i = 0; i < complex_length; ++i)
  {
    complex[i].re = 2*i;
    complex[i].im = 2*i + 1;
  }

  double *r_complex = reinterpret_cast<double*>(complex);

  for (size_t i=1; i < 2*complex_length; ++i)
  {
    EXPECT_EQ(r_complex[i], r_complex[i-1] + 1);
  }

  for (size_t i=0; i < 2*complex_length; ++i)
  {
    real[i] = i;
  }

  wipp::wipp_complex_t *r_real = reinterpret_cast<wipp::wipp_complex_t*>(real);

  for (size_t i = 0; i < complex_length; ++i)
  {
    EXPECT_EQ(r_real[i].re, 2*i);
    EXPECT_EQ(r_real[i].im, 2*i + 1);
  }

}


TEST(testTriangle, triangle)
{

  for (size_t length = 10; length < 512; length = length + 13)
  {
    DEBUG_STREAM("LENGTH: " << length);
    double frame[length];
    wipp::triangle(frame, length);

    for (size_t i = 0; i < length; ++i)
    {
      if (i == 0)
      {
	TRACE_STREAM("i: " << i << " " << frame[i]);
	EXPECT_NEAR(frame[i], 0, 0.0016);
      }
      else if (i == length -1)
      {
	TRACE_STREAM("i: " << i << " " << frame[i]);
	EXPECT_NEAR(frame[i], 0, (2.0F/length)*1.05);
      }
      else if (length%2 == 0 && (i == length/2 ||i == length/2 -1) )
      {
	TRACE_STREAM("i: " << i << " " << frame[i]);
	if (length < 20)
	  EXPECT_NEAR(frame[i],1, 0.2);
	else if (length < 100)
	  EXPECT_NEAR(frame[i],1, 0.06);
	else
	  EXPECT_NEAR(frame[i],1, 0.02);
      }
      else if (length%2 == 1 && i == length/2 )
      {
	TRACE_STREAM("i: " << i << " " << frame[i]);
	EXPECT_NEAR(frame[i],1, 0.1);
      }
      else if ( (i > length/2-2 && i < length/2 + 2) || (i < 5) || (i > length-4))
      {
	TRACE_STREAM("i: " << i << " " << frame[i]);
      }
      else if (i < length/2)
      {
	EXPECT_LT(frame[i-1], frame[i]);
      }
      else
      {
	EXPECT_GT(frame[i-1], frame[i]);
      }
    }
  }
}

template <typename T>
void testRamp(T *buffer, int length, double min, double max, double slope)
{
  wipp::ramp(buffer, length, min, slope);
  EXPECT_EQ(buffer[0], static_cast<T>(min));
  for (size_t i = 1; i < length; ++i)
  {
    EXPECT_GE(buffer[i], buffer[i-1]);
    EXPECT_NEAR(buffer[i] - buffer[i-1], static_cast<T>(slope), 1);
  }
}

TEST(testMedian, median)
{
  size_t length = 5;
  int buffer[]     = {3,4,16,5,7};
   int median;

  wipp::median(&buffer[0], length, &median);
  EXPECT_EQ(median, 5);


  double dbuffer[]   ={0.1,0.5,0.3,0.8,0.2,0.9,0.4,0.2,0.7,0.009,0.7,0.5,0.3,0.2,10.5,0.4,0.3,0.8,0.7,0.9,0.7,0.9,0.5,0.1,0.5,60.7,90.8,0.7,0.5,0.4,0.009,0.7,0.5,0.4,0.3,0.1,0.6,0.8,0};

  length = 39;
  double dmedian;
  wipp::median(&dbuffer[0], length, &dmedian);
  EXPECT_EQ(dmedian, 0.5);

}


TEST(testMedian, median_filter)
{
  int length = 20;
  int buffer[] =    {1, 2, 3, 20, 5, 6, -60, 8, 9, 10, 12, 9, 8, 7, 2, 5, 4, 3, -30, 1};
  int reference[] = {1, 2, 3,  5, 5, 6,   6, 8, 9,  9,  9, 9, 8, 7, 5, 4, 3, 3,  1, 1};
  int obuffer[length];

  median_filter(buffer, obuffer, length, 5);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_EQ(reference[i], obuffer[i]);
  }

  median_filter(buffer, length, 5);
  for (size_t i = 0; i < length; ++i)
  {
    EXPECT_EQ(reference[i], buffer[i]);
  }

}

TEST(testRamp, ramp)
{
  const size_t length = 1000;
  const double min = 100;
  const double max = M_PI*1000;
  const double slope = 30;

  double dbuffer[length];
  testRamp(dbuffer, length, min, max, slope);
  int ibuffer[length];
  testRamp(ibuffer, length, min, max, slope);
  float fbuffer[length];
  testRamp(fbuffer, length, min, max, slope);
  uint16_t ubuffer[length];
  testRamp(ubuffer, length, min, max, slope);

}


TEST(signal, tone)
{
  size_t length=1024;
  double d_buffer[length];
  int i_buffer[length];
  float f_buffer[length];
  double phase = M_PI/3;
  double magnitude = 1.4;
  double frequency = 0.34;

  tone(d_buffer, length, magnitude, frequency, phase);
  tone(f_buffer, length, magnitude, frequency, phase);
  tone(i_buffer, length, magnitude, frequency, phase);


  for (int i = 0; i < length; ++i)
  {
    double value = magnitude*sin(2*M_PI*frequency*static_cast<double>(i) + phase);
    EXPECT_DOUBLE_EQ(value, d_buffer[i]);
    EXPECT_FLOAT_EQ(static_cast<float>(value), f_buffer[i]);
    EXPECT_EQ(static_cast<int>(value), i_buffer[i]);
  }

}

TEST(stats, maxAbs)
{
    double source[10] = {1, -200, 3, 4, 5, 60.56, 7, 8, 9, 10};
    double max;

    wipp::max(source, 10, &max);
    EXPECT_DOUBLE_EQ(60.56, max);
    wipp::maxAbs(source, 10, &max);
    EXPECT_DOUBLE_EQ(200, max);
}

TEST(testTriangle, asym_triangle)
{

//  _logger_.setLogLevel(Logger::TRACE);

  for (float flength = 100; flength < 512; flength += 13)
  {
    int length = static_cast<int>(flength+0.5);

    double frame[length];

    for (float fperiod = std::max(0.2F*length, 100.0F); fperiod < 1.2*length; fperiod *= 1.3)
    {
      int period = static_cast<int>(fperiod+0.5);

      for (float phase = 0; phase < 2*M_PI; phase += 0.3)
      {

	for (float offset = 0; offset < 2; offset += 0.2)
	{

	  for (float asym = -2*M_PI/3; asym < 2*M_PI/3; asym += M_PI/5)
	  {

	    wipp::triangle(frame, length, period, phase, asym, offset);
	    //	    save_buffer(frame, length, "frame");

	    size_t i = 0;
	    double n = (period/(4*M_PI))*phase + 0.5; // i-> buffer index, n -> sample within triangle period?
	    const double center = period*(asym/(2*M_PI) + 0.5);

	    DEBUG_STREAM("PERIOD: " << period <<
			 ", PHASE: " << phase <<
			 ", LENGTH: " << length <<
			 ", OFFSET: " << offset <<
			 ", ASYM: " << asym <<
			 ", CENTER: " << center <<
			 ", N: " << n);


	    for (n++, i = 1; i < length; ++i, ++n)
	    {

	      TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n);

	      if (n >= period) n = n - period;

	      if (n == 0)
	      {
		TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n);
		EXPECT_NEAR(frame[i], offset , 0.01);
	      }
	      else if (n == period -1 )
	      {
		TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n << " (END PERIOD)");
		EXPECT_NEAR(frame[i], offset + 1/(period - center), 0.01);
	      }
	      else if (period%2 == 0 && (n == center || n == center -1) )
	      {
		TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n);
		if (period < 20)
		  EXPECT_NEAR(frame[i],1 + offset, 0.82);
		else if (period < 100)
		  EXPECT_NEAR(frame[i],1 + offset, 0.15);
		else
		  EXPECT_NEAR(frame[i],1 + offset, 0.1);
	      }
	      else if (period%2 == 1 && n == center )
	      {
		TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n);
		EXPECT_NEAR(frame[i],1 + offset, 0.5);
	      }
	      else if ( (n > center-2 && n < center + 2) || (n < 5) || (n > period-4))
	      {
		TRACE_STREAM("i: " << i << " " << frame[i] << " n: " << n);
	      }
	      else if (n < center )
	      {
		TRACE_STREAM(frame[i-1] << " <  " << frame[i] << " c: " << i << " " << n << " " << center);
		EXPECT_LE(frame[i-1], frame[i]);
	      }
	      else
	      {
		EXPECT_GE(frame[i-1], frame[i]);
	      }
	    }
	  }
	}
      }
    }
  }
}


}
}


int main(int argc, char* argv[])
{
  try
  {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
  catch (...)
  {
    std::cerr << "WIPP tests failed" << std::endl;
  }
}
