/*
* ipputils.inl
* Copyright 2016 (c) Jordi Adell
* Created on: 2015
* 	Author: Jordi Adell - adellj@gmail.com
*
* This file is part of WIPP
*
* WIPP is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WIPP is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with WIPP.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <wipp/wipputils.h>

#include <ippcore.h>
#include <ipps.h>

namespace wipp{

  void copyBuffer(const int16_t *inbuffer, int16_t *outbuffer, size_t length)
  {
    ippsCopy_16s(inbuffer, outbuffer, length);
  }

  void copyBuffer(const int32_t *inbuffer, int32_t *outbuffer, size_t length)
  {
    ippsCopy_32s(inbuffer, outbuffer, length);
  }

  void copyBuffer(const double *inbuffer, double *outbuffer, size_t length)
  {
    ippsCopy_64f(inbuffer, outbuffer, length);
  }

  void copyBuffer(const float *inbuffer, float *outbuffer, size_t length)
  {
    ippsCopy_32f(inbuffer, outbuffer, length);
  }

  void copyBuffer(const float *inbuffer, double *outbuffer, size_t length)
  {
    ippsConvert_32f64f(inbuffer, outbuffer, length);
  }

  void copyBuffer(const double *inbuffer, float *outbuffer, size_t length)
  {
    ippsConvert_64f32f(inbuffer, outbuffer, length);
  }

  /* @TODO For conversions that invole int16_t integers an scaling could be performed.
   * If the input buffer is of type int16_t, then then values of the buffers are multiplied by
   * 2^(-15) = 1/32768
   * before to convert then into a floating point value.
   * If the output buffer is a int16_t integer then the floating point value are multiplied by
   * 2^(15) to restore the original dynamic range. If there are value above 1 they are sturated to (2^15-1)
   * (see Intel® Integrated Performance Primitives for Intel® Architecture. Reference Manual, Volume 1: Signal Processing)
   * But this is a bit dangerous if we use different functions for int2float and float2int conversions.
   **/

  void copyBuffer(const int16_t *inbuffer, float *outbuffer, size_t length)
  {
    ippsConvert_16s32f_Sfs(inbuffer, outbuffer, length, 0);
  }

  void copyBuffer(const int16_t *inbuffer, double *outbuffer, size_t length)
  {
    ippsConvert_16s64f_Sfs(inbuffer, outbuffer, length, 0);
  }

  void copyBuffer(const int32_t *inbuffer, float *outbuffer, size_t length)
  {
    ippsConvert_32s32f_Sfs(inbuffer, outbuffer, length, 0);
  }

  void copyBuffer(const int32_t *inbuffer, double *outbuffer, size_t length)
  {
    ippsConvert_32s64f_Sfs(inbuffer, outbuffer, length, 0);
  }

  void copyBuffer(const double *inbuffer, int16_t *outbuffer, size_t length)
  {
    ippsConvert_64f16s_Sfs(inbuffer, outbuffer, length, ippRndFinancial, 0);
  }

  void copyBuffer(const double *inbuffer, uint16_t *outbuffer, size_t length)
  {
    Ipp32f tmp[length];
    copyBuffer(inbuffer, tmp,  length);
    copyBuffer(tmp, outbuffer, length);
  }

  void copyBuffer(const float *inbuffer, int16_t *outbuffer, size_t length)
  {
    ippsConvert_32f16s_Sfs(inbuffer, outbuffer, length, ippRndFinancial, 0);
  }

  void copyBuffer(const float *inbuffer, int16_t uint32_t *outbuffer, size_t length)
  {
    ippsConvert_32f16u_Sfs(inbuffer, outbuffer, length, ippRndFinancial, 0);
  }

  void subBuffer_I(const int16_t *inbuffer, int16_t *outbuffer, size_t length)
  {
    ippsSub_16s_I(inbuffer, outbuffer, length);
  }

  void subBuffer_I(const float *inbuffer, float *outbuffer, size_t length)
  {
    ippsSub_32f_I(inbuffer, outbuffer, length);
  }

  void subBuffer_I(const double *inbuffer, double *outbuffer, size_t length)
  {
    ippsSub_64f_I(inbuffer, outbuffer, length);
  }

}

