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

    long int imin = std::numeric_limits<int>::min();
    long int imax = std::numeric_limits<int>::max();

    DEBUG_STREAM(" min: " << fmin << " max: " << fmax << " : " << 2*(fmin/3) + fmax/3 << " " << 2*fmin/3);

    double inDbuffer[len] = {dmin, 2*(dmin/3) + dmax/3, dmin + 2*(dmax/3), dmax};
    float  inFbuffer[len] = {fmin, 2*(fmin/3) + fmax/3, fmin/3 + 2*(fmax/3), fmax};
    short  inSbuffer[len] = {smin, static_cast<short>(2*(smin/3) + smax/3), static_cast<short>(smin/3 + 2*(smax/3)), smax};
    int   inIbuffer[len] = {smin, static_cast<long> (2*(imin/3) + imax/3), static_cast<long> (imin/3 + 2*(imax/3)), imax};

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


TEST(circularBufferTest, init_delete)
{
  wipp::wipp_circular_buffer_t *cf;
  wipp::init_cirular_buffer<double>(&cf, 1024);

  EXPECT_FALSE(cf == NULL);

  wipp::delete_circular_buffer(&cf);

  EXPECT_TRUE(cf == NULL);

  wipp::delete_circular_buffer(&cf);

}



TEST(fftTest, init_delete)
{
  wipp::wipp_fft_t *fft;
  wipp::init_wipp_fft(&fft, 512);

  EXPECT_FALSE(fft == NULL);

  wipp::delete_wipp_fft(&fft);

  EXPECT_TRUE(fft == NULL);

  wipp::delete_wipp_fft(&fft);

}


}
}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
