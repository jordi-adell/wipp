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

#ifndef DEBUG_STREAM
#define DEBUG_STREAM(x)
#endif

#include <limits>
namespace wipp
{
namespace test
{


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
    std::cout << "order: " << n << std::endl;

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

}


TEST(fftTest, init_delete)
{

  for (int i = 0; i < 15; ++i)
  {
    std::cout << "order: " << (1 << i) << std::endl;
    wipp::wipp_fft_t *fft;
    wipp::init_wipp_fft(&fft, 1 << i);

    EXPECT_FALSE(fft == NULL);

    wipp::delete_wipp_fft(&fft);

    EXPECT_TRUE(fft == NULL);

    wipp::delete_wipp_fft(&fft);
  }


  for (int i = 1; i < 512; ++i)
  {
    if (i % 100 == 0)
      std::cout << "up to order: " << i << std::endl;
    wipp::wipp_fft_t *fft;
    wipp::init_wipp_fft(&fft, i);

    EXPECT_FALSE(fft == NULL);

    wipp::delete_wipp_fft(&fft);

    EXPECT_TRUE(fft == NULL);

    wipp::delete_wipp_fft(&fft);
  }

}


}
}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
