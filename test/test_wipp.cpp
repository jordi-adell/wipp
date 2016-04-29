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

    int imin = std::numeric_limits<int>::min();
    int imax = std::numeric_limits<int>::max();

    DEBUG_STREAM(" min: " << fmin << " max: " << fmax << " : " << 2*(fmin/3) + fmax/3 << " " << 2*fmin/3);

    double inDbuffer[len] = {dmin, 2*(dmin/3) + dmax/3, dmin + 2*(dmax/3), dmax};
    float  inFbuffer[len] = {fmin, 2*(fmin/3) + fmax/3, fmin/3 + 2*(fmax/3), fmax};
    short  inSbuffer[len] = {smin, static_cast<short>(2*(smin/3) + smax/3), static_cast<short>(smin/3 + 2*(smax/3)), smax};
    int inIbuffer[len] =  {smin, static_cast<int> (2*(imin/3) + imax/3), static_cast<int> (imin/3 + 2*(imax/3)), imax};

    double oDbuffer[len];
    float  oFbuffer[len];
    short  oSbuffer[len];
    int   oIbuffer[len];

    // Check equal resolution
    copyBuffer(inDbuffer, oDbuffer, len);
    copyBuffer(inFbuffer, oFbuffer, len);
    copyBuffer(inSbuffer, oSbuffer, len);
    copyBuffer(inIbuffer, oIbuffer, len);

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
//      std::ofstream sfs("signal.txt");
      for (size_t i = 0; i < length; ++i)
      {
	signal[i] = 2*cos(2*M_PI*freq*i);
//	sfs << signal[i] << std::endl;
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
//      INFO_STREAM("Filtered Power " << freq << ": " << gain << " dB");

      if (freq < lf*0.9)
	EXPECT_LT(gain, -15);
      else if (lf*1.1 < freq && freq < hf*0.9)
	EXPECT_NEAR(0, gain, 10);
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

  //  std::ofstream ofss("tmp1.txt");
  //  for (int i = 0; i < length; ++i)
  //    ofss << frame[i] << std::endl;

  wipp::wipp_fft_t *fft;
  wipp::init_fft(&fft, length);
  wipp::fft(frame, spectrum, fft);
  wipp::magnitude(reinterpret_cast<wipp_complex_t*>(frame), magnitude, length/2);
  wipp::power(magnitude, length/2);

  //  std::ofstream ofsm("tmp2.txt");
  //  for (int i = 0; i < length/2; ++i)
  //    ofsm << magnitude[i] << std::endl;

  wipp::delete_fft(&fft);
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


TEST(fftTest, transform)
{
  size_t fft_length = 256;
  wipp::wipp_fft_t *fft;
  wipp::init_fft(&fft, fft_length);

  double signal[fft_length];
  double isignal[fft_length];
  double signal_fft[fft_length];

  double freq = 0.08;

  for (size_t i = 0; i < fft_length; ++i)
  {
    signal[i] = sin(2*M_PI*freq*i);
  }

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
				-0.3191, 0.0033, -0.3188, 0.0025, -0.3186, 0.0016, -0.3185, 0.0008};

  //  save_buffer(signal, fft_length, "signal");

  wipp::fft(signal, signal_fft, fft);

  for (size_t i = 0; i < fft_length; ++i)
  {
    EXPECT_NEAR(signal_fft[i], fft_ref[i], 1e-4);
  }

//  save_buffer(signal_fft, fft_length, "signal_fft");

  wipp::ifft(signal_fft, isignal, fft);

  for (size_t i = 0; i < fft_length; ++i)
  {
    EXPECT_NEAR(signal[i], isignal[i]/fft_length, 1e-12);
  }

  //  save_buffer(isignal, fft_length, "isignal");

  wipp::delete_fft(&fft);
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
	EXPECT_EQ(frame[i],0);
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
