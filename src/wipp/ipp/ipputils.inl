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
#include <math.h>

#define IPP64fc(x) reinterpret_cast<Ipp64fc*>(x)
#define cIPP64fc(x) reinterpret_cast<const Ipp64fc*>(x)

template<typename T>
inline void std_sqrt(const T &value, T &sqrt_value)
{
    sqrt_value = sqrt(value);
}

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

    void copyBuffer(const uint16_t *inbuffer, uint16_t *outbuffer, size_t length)
    {
        memccpy(outbuffer, inbuffer, length, sizeof(uint16_t));
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

    void copyBuffer(const uint16_t *inbuffer, float *outbuffer, size_t length)
    {
        ippsConvert_16u32f(inbuffer, outbuffer, length);
    }

    void copyBuffer(const uint16_t *inbuffer, double *outbuffer, size_t length)
    {
        Ipp32f intermediateBuffer[length];
        ippsConvert_16u32f(inbuffer, intermediateBuffer, length);
        ippsConvert_32f64f(intermediateBuffer, outbuffer, length);
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

  void copyBuffer(const float *inbuffer, uint16_t *outbuffer, size_t length)
  {
    ippsConvert_32f16u_Sfs(inbuffer, outbuffer, length, ippRndFinancial, 0);
  }

    void copyBuffer(const double *inbuffer, int32_t *outbuffer, size_t length) {
        ippsConvert_64f32s_Sfs(inbuffer, outbuffer, length, ippRndFinancial, 0);
    }

    void copyBuffer(const double *inbuffer, uint32_t *outbuffer, size_t length) {
        for (size_t i = 0;i < length; ++i)
            outbuffer[i] = inbuffer[i];
    }

    void copyBuffer(const uint32_t *inbuffer, double *outbuffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            outbuffer[i] = inbuffer[i];
    }

    void copyBuffer(const wipp_complex_t *inbuffer, wipp_complex_t *outbuffer, size_t length) {
        ippsCopy_64fc(cIPP64fc(inbuffer), IPP64fc(outbuffer), length);
    }

    void set(double val, double *buffer, size_t length) {
        ippsSet_64f(val, buffer, length);
    }

    void set(float val, float *buffer, size_t length) {
        ippsSet_32f(val, buffer, length);
    }

    void set(int16_t val, int16_t *buffer, size_t length) {
        ippsSet_16s(val, buffer, length);
    }

    void set(int32_t val, int32_t *buffer, size_t length) {
        ippsSet_32s(val, buffer, length);
    }

    void set(uint32_t val, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = val;
    }

    void set(uint16_t val, uint16_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = val;
    }

    void set(wipp_complex_t val, wipp_complex_t * buffer, size_t length) {
        ippsSet_64fc(*IPP64fc(&val), IPP64fc(buffer), length);
    }

    void setZeros(double *buffer, size_t length) {
        ippsZero_64f(buffer, length);
    }

    void setZeros(float *buffer, size_t length) {
        ippsZero_32f(buffer, length);
    }

    void setZeros(int16_t *buffer, size_t length) {
        ippsZero_16s(buffer, length);
    }

    void setZeros(int32_t *buffer, size_t length) {
        ippsZero_32s(buffer, length);
    }

    void setZeros(uint32_t *buffer, size_t length) {
        memset(reinterpret_cast<void*>(buffer), 0, sizeof(*buffer)*length);
    }

    void setZeros(uint16_t *buffer, size_t length) {
        memset(reinterpret_cast<void*>(buffer), 0, sizeof(*buffer)*length);
    }

    void setZeros(wipp_complex_t * buffer, size_t length) {
        ippsZero_64fc(IPP64fc(buffer), length);
    }


    void add(const double *buffer_a, double *buffer_b, size_t length) {
        ippsAdd_64f_I(buffer_a, buffer_b, length);
    }

    void add(const float *buffer_a, float* buffer_b, size_t length) {
        ippsAdd_32f_I(buffer_a, buffer_b, length);
    }

    void add(const int16_t *buffer_a, int16_t* buffer_b, size_t length) {
        ippsAdd_16s_I(buffer_a, buffer_b, length);
    }

    void add(const int32_t *buffer_a, int32_t* buffer_b, size_t length) {
        ippsAdd_32s_ISfs(buffer_a, buffer_b, length, 0);
    }

    void add(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length) {
        ippsAdd_16u_ISfs(buffer_a, buffer_b, length, 0);
    }

    void add(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        Ipp64f intermediate_buffer_b[length];
        Ipp64f destination[length];
        ippsAdd_64f(intermediate_buffer_a, intermediate_buffer_b, destination, length);
        for (size_t i = 0; i < length; ++i)
            buffer_b[i] = destination[i];
    }

    void add(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length) {
        ippsAdd_64fc_I(cIPP64fc(buffer_a), IPP64fc(buffer_b), length);
    }

    void add(const double *buffer_a, const double* buffer_b, double * buffer, size_t length) {
        ippsAdd_64f(buffer_a, buffer_b, buffer, length);
    }

    void add(const float *buffer_a, const float* buffer_b, float * buffer, size_t length) {
        ippsAdd_32f(buffer_a, buffer_b, buffer, length);
    }

    void add(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length) {
        ippsAdd_16s(buffer_a, buffer_b, buffer, length);
    }

    void add(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length) {
        ippsAdd_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void add(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length) {
        ippsAdd_16u(buffer_a, buffer_b, buffer, length);
    }

    void add(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length) {
        ippsAdd_32u(buffer_a, buffer_b, buffer, length);
    }

    void add(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b,
             wipp::wipp_complex_t * buffer, size_t length) {
        ippsAdd_64fc(cIPP64fc(buffer_a), cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }


    void sub(const double *buffer_a, double* buffer_b, size_t length) {
        ippsSub_64f_I(buffer_a, buffer_b, length);
    }

    void sub(const float *buffer_a, float* buffer_b, size_t length) {
        ippsSub_32f_I(buffer_a, buffer_b, length);
    }

    void sub(const int16_t *buffer_a, int16_t* buffer_b, size_t length) {
        ippsSub_16s_I(buffer_a, buffer_b, length);
    }

    void sub(const int32_t *buffer_a, int32_t* buffer_b, size_t length) {
        ippsSub_32s_ISfs(buffer_a, buffer_b, length, 0);
    }

    void sub(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length) {
        ippsSub_16u_ISfs(buffer_a, buffer_b, length, 0);
    }

    void sub(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        Ipp64f intermediate_buffer_b[length];
        Ipp64f destination[length];
        copyBuffer(buffer_a, intermediate_buffer_a, length);
        copyBuffer(buffer_b, intermediate_buffer_b, length);
        ippsSub_64f(intermediate_buffer_a, intermediate_buffer_b, destination, length);
        copyBuffer(destination, buffer_b, length);
    }

    void sub(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length) {
        ippsSub_64fc_I(cIPP64fc(buffer_a), IPP64fc(buffer_b), length);
    }

    void sub(const double *buffer_a, const double* buffer_b, double * buffer, size_t length) {
        ippsSub_64f(buffer_a, buffer_b, buffer, length);
    }

    void sub(const float *buffer_a, const float* buffer_b, float * buffer, size_t length) {
        ippsSub_32f(buffer_a, buffer_b, buffer, length);
    }

    void sub(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length) {
        ippsSub_16s(buffer_a, buffer_b, buffer, length);
    }

    void sub(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length) {
        ippsSub_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void sub(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length) {
        ippsSub_16u_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void sub(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        Ipp64f intermediate_buffer_b[length];
        Ipp64f destination[length];
        copyBuffer(buffer_a, intermediate_buffer_a, length);
        copyBuffer(buffer_b, intermediate_buffer_b, length);
        ippsSub_64f(intermediate_buffer_a, intermediate_buffer_b, destination, length);
        copyBuffer(destination, buffer, length);
    }

    void sub(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b,
             wipp::wipp_complex_t * buffer, size_t length) {
        ippsSub_64fc(cIPP64fc(buffer_a), cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }



    void mult(const double *buffer_a, const double *buffer_b, double *buffer, size_t length) {
        ippsMul_64f(buffer_a, buffer_b, buffer, length);
    }

    void mult(const float *buffer_a, const float *buffer_b, float *buffer, size_t length) {
        ippsMul_32f(buffer_a, buffer_b, buffer, length);
    }

    void mult(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) {
        ippsMul_16s(buffer_a, buffer_b, buffer, length);
    }

    void mult(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) {
        ippsMul_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void mult(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) {
        ippsMul_16u_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void mult(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        Ipp64f intermediate_buffer_b[length];
        Ipp64f destination[length];
        copyBuffer(buffer_a, intermediate_buffer_a, length);
        copyBuffer(buffer_b, intermediate_buffer_b, length);
        ippsMul_64f(intermediate_buffer_a, intermediate_buffer_b, destination, length);
        copyBuffer(destination, buffer, length);
    }

    void mult(const double *buffer_a, double *buffer_b, size_t length) {
        ippsMul_64f_I(buffer_a, buffer_b, length);
    }

    void mult(const float *buffer_a, float *buffer_b, size_t length) {
        ippsMul_32f_I(buffer_a, buffer_b, length);
    }

    void mult(const int16_t *buffer_a, int16_t *buffer_b, size_t length) {
        ippsMul_16s_I(buffer_a, buffer_b, length);
    }

    void mult(const int32_t *buffer_a, int32_t *buffer_b, size_t length) {
        ippsMul_32s_ISfs(buffer_a, buffer_b, length, 0);
    }

    void mult(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length) {
        ippsMul_16u_ISfs(buffer_a, buffer_b, length, 0);
    }

    void mult(const uint32_t *buffer_a, uint32_t *buffer_b, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        Ipp64f intermediate_buffer_b[length];
        Ipp64f destination[length];
        copyBuffer(buffer_a, intermediate_buffer_a, length);
        copyBuffer(buffer_b, intermediate_buffer_b, length);
        ippsMul_64f(intermediate_buffer_a, intermediate_buffer_b, destination, length);
        copyBuffer(destination, buffer_b, length);
    }

    void mult(const double *buffer_a, wipp_complex_t *buffer_b, size_t length) {
        Ipp64fc intermediate_buffer_a[length];
        ippsRealToCplx_64f(buffer_a, NULL, intermediate_buffer_a, length);
        ippsMul_64fc_I(intermediate_buffer_a, IPP64fc(buffer_b), length);
    }

    void mult(const double *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length) {
        Ipp64fc intermediate_buffer_a[length];
        ippsRealToCplx_64f(buffer_a, NULL, intermediate_buffer_a, length);
        ippsMul_64fc(intermediate_buffer_a, cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }

    void mult(const float *buffer_a, wipp_complex_t *buffer_b, size_t length) {
        Ipp64f intermeidate_buffer_a[length];
        copyBuffer(buffer_a, intermeidate_buffer_a, length);
        Ipp64fc intermediate_complex_a[length];
        ippsRealToCplx_64f(intermeidate_buffer_a, NULL, intermediate_complex_a, length);
        ippsMul_64fc_I(intermediate_complex_a, IPP64fc(buffer_b), length);
    }

    void mult(const float *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length) {
        Ipp64f intermediate_buffer_a[length];
        copyBuffer(buffer_a, intermediate_buffer_a, length);
        Ipp64fc intermediate_complex_a[length];
        ippsRealToCplx_64f(intermediate_buffer_a, NULL, intermediate_complex_a, length);
        ippsMul_64fc(intermediate_complex_a, cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }

    void mult(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length) {
        ippsMul_64fc_I(cIPP64fc(buffer_a), IPP64fc(buffer_b), length);
    }

    void mult(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b,
              wipp_complex_t *buffer, size_t length) {
        ippsMul_64fc(cIPP64fc(buffer_a), cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }


    void div(const double *buffer_a, const double *buffer_b, double *buffer, size_t length) {
        ippsDiv_64f(buffer_a, buffer_b, buffer, length);
    }

    void div(const float *buffer_a, const float *buffer_b, float *buffer, size_t length) {
        ippsDiv_32f(buffer_a, buffer_b, buffer, length);
    }

    void div(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) {
        ippsDiv_16s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void div(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) {
        ippsDiv_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void div(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) {
        ippsDiv_16u_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void div(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = buffer_b[i] / buffer_a[i];
    }

    void div(const double *buffer_a, double *buffer_b, size_t length) {
        ippsDiv_64f_I(buffer_a, buffer_b, length);
    }

    void div(const float *buffer_a, float *buffer_b, size_t length) {
        ippsDiv_32f_I(buffer_a, buffer_b, length);
    }

    void div(const int16_t *buffer_a, int16_t *buffer_b, size_t length) {
        ippsDiv_16s_ISfs(buffer_a, buffer_b, length, 0);
    }

    void div(const int32_t *buffer_a, int32_t *buffer_b, size_t length) {
        ippsDiv_32s_ISfs(buffer_a, buffer_b, length, 0);
    }

    void div(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length) {
        ippsDiv_16u_ISfs(buffer_a, buffer_b, length, 0);
    }

    void div(const uint32_t *buffer_a, uint32_t *buffer_b, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_b[i] = buffer_b[i] / buffer_a[i];
    }

    void div(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b,
             wipp_complex_t *buffer, size_t length) {
        ippsDiv_64fc(cIPP64fc(buffer_a), cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }

    void div(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length) {
        ippsDiv_64fc_I(cIPP64fc(buffer_a), IPP64fc(buffer_b), length);
    }

    void addC(double C, const double *buffer_in, double *buffer_out, size_t length) {
        ippsAddC_64f(buffer_in, C, buffer_out, length);
    }

    void addC(float C, const float *buffer_in, float *buffer_out, size_t length) {
        ippsAddC_32f(buffer_in, C, buffer_out, length);
    }

    void addC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsAddC_16s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void addC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        ippsAddC_32s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void addC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        ippsAddC_16u_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void addC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = C*buffer_in[i];
    }

    void addC(double C, double *buffer, size_t length) {
        ippsAddC_64f_I(C, buffer, length);
    }

    void addC(float C, float *buffer, size_t length) {
        ippsAddC_32f_I(C, buffer, length);
    }

    void addC(int16_t C, int16_t *buffer, size_t length) {
        ippsAddC_16s_I(C, buffer, length);
    }

    void addC(int32_t C, int32_t *buffer, size_t length) {
        ippsAddC_32s_ISfs(C, buffer, length, 0);
    }

    void addC(uint16_t C, uint16_t *buffer, size_t length) {
        ippsAddC_16u_ISfs(C, buffer, length, 0);
    }

    void addC(uint32_t C, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = buffer[i] + C;
    }

    void addC(wipp_complex_t C, wipp_complex_t *buffer, size_t length) {
        ippsAddC_64fc_I(*IPP64fc(&C), IPP64fc(buffer), length);
    }

    void subC(double C, const double *buffer_in, double *buffer_out, size_t length) {
        ippsSubC_64f(buffer_in, C, buffer_out, length);
    }

    void subC(float C, const float *buffer_in, float *buffer_out, size_t length) {
        ippsSubC_32f(buffer_in, C, buffer_out, length);
    }

    void subC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsSubC_16s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void subC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        ippsSubC_32s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void subC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        ippsSubC_16u_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void subC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = buffer_in[i] - C;
    }

    void subC(double C, double *buffer, size_t length) {
        ippsSubC_64f_I(C, buffer, length);
    }

    void subC(float C, float *buffer, size_t length) {
        ippsSubC_32f_I(C, buffer, length);
    }

    void subC(int16_t C, int16_t *buffer, size_t length) {
        ippsSubC_16s_I(C, buffer, length);
    }

    void subC(int32_t C, int32_t *buffer, size_t length) {
        ippsSubC_32s_ISfs(C, buffer, length, 0);
    }

    void subC(uint16_t C, uint16_t *buffer, size_t length) {
        ippsSubC_16u_ISfs(C, buffer, length, 0);
    }

    void subC(uint32_t C, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] -= C;
    }

    void multC(double C, const double *buffer_in, double *buffer_out, size_t length) {
        ippsMulC_64f(buffer_in, C, buffer_out, length);
    }

    void multC(float C, const float *buffer_in, float *buffer_out, size_t length) {
        ippsMulC_32f(buffer_in, C, buffer_out, length);
    }

    void multC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsMulC_16s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void multC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        ippsMulC_32s_Sfs(buffer_in, C , buffer_out, length, 0);
    }

    void multC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        ippsMulC_16u_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void multC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = buffer_in[i]*C;
    }

    void multC(double C, double *buffer, size_t length) {
        ippsMulC_64f_I(C, buffer, length);
    }

    void multC(float C, float *buffer, size_t length) {
        ippsMulC_32f_I(C, buffer, length);
    }

    void multC(int16_t C, int16_t *buffer, size_t length) {
        ippsMulC_16s_ISfs(C, buffer, length, 0);
    }

    void multC(int32_t C, int32_t *buffer, size_t length) {
        ippsMulC_32s_ISfs(C, buffer, length, 0);
    }

    void multC(uint16_t C, uint16_t *buffer, size_t length) {
        ippsMulC_16u_ISfs(C, buffer, length, 0);
    }

    void multC(uint32_t C, uint32_t *buffer, size_t length) {
        for(size_t i = 0; i < length; ++i)
            buffer[i] *= C;
    }

    void divC(double C, const double *buffer_in, double *buffer_out, size_t length) {
        ippsDivC_64f(buffer_in, C, buffer_out, length);
    }

    void divC(float C, const float *buffer_in, float *buffer_out, size_t length) {
        ippsDivC_32f(buffer_in, C, buffer_out, length);
    }

    void divC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsDivC_16s_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void divC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = buffer_in[i] / C;
    }

    void divC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        ippsDivC_16u_Sfs(buffer_in, C, buffer_out, length, 0);
    }

    void divC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = buffer_in[i] / C;
    }

    void divC(double C, double *buffer, size_t length) {
        ippsDivC_64f_I(C, buffer, length);
    }

    void divC(float C, float *buffer, size_t length) {
        ippsDivC_32f_I(C, buffer, length);
    }

    void divC(int16_t C, int16_t *buffer, size_t length) {
        ippsDivC_16s_ISfs(C, buffer, length, 0);
    }

    void divC(int32_t C, int32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] /= C;
    }

    void divC(uint16_t C, uint16_t *buffer, size_t length) {
        ippsDivC_16u_ISfs(C, buffer, length, 0);
    }

    void divC(uint32_t C, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] /= C;
    }

    void addProduct(const double* buffer_a, const double *buffer_b,
                    const double *buffer_c, double *buffer, size_t length) {
        copyBuffer(buffer_c, buffer, length);
        ippsAddProduct_64f(buffer_a, buffer_b, buffer, length);
    }

    void addProduct(const float* buffer_a, const float *buffer_b,
                    const float *buffer_c, float *buffer, size_t length) {
        copyBuffer(buffer_c, buffer, length);
        ippsAddProduct_32f(buffer_a, buffer_b, buffer, length);
    }

    void addProduct(const int16_t* buffer_a, const int16_t *buffer_b,
                    const int16_t *buffer_c, int16_t *buffer, size_t length) {
        copyBuffer(buffer_c, buffer, length);
        ippsAddProduct_16s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void addProduct(const int32_t* buffer_a, const int32_t *buffer_b,
                    const int32_t *buffer_c, int32_t *buffer, size_t length) {
        copyBuffer(buffer_c, buffer, length);
        ippsAddProduct_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void addProduct(const uint16_t* buffer_a, const uint16_t *buffer_b,
                    const uint16_t *buffer_c, uint16_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = buffer_c[i] + buffer_a[i]*buffer_b[i];
    }

    void addProduct(const uint32_t* buffer_a, const uint32_t *buffer_b,
                    const uint32_t *buffer_c, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = buffer_c[i] + buffer_a[i]*buffer_b[i];
    }

    void addProduct(const wipp_complex_t* buffer_a, const wipp_complex_t *buffer_b,
                    const wipp_complex_t *buffer_c, wipp_complex_t *buffer, size_t length) {
        copyBuffer(buffer_c, buffer, length);
        ippsAddProduct_64fc(cIPP64fc(buffer_a), cIPP64fc(buffer_b), IPP64fc(buffer), length);
    }

    void addProduct(const double* buffer_a, const double *buffer_b, double *buffer, size_t length) {
        ippsAddProduct_64f(buffer_a, buffer_b, buffer, length);
    }

    void addProduct(const float* buffer_a, const float *buffer_b, float *buffer, size_t length) {
        ippsAddProduct_32f(buffer_a, buffer_b, buffer, length);
    }

    void addProduct(const int16_t* buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) {
        ippsAddProduct_16s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void addProduct(const int32_t* buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) {
        ippsAddProduct_32s_Sfs(buffer_a, buffer_b, buffer, length, 0);
    }

    void addProduct(const uint16_t* buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] += buffer_a[i]*buffer_b[i];
    }

    void addProduct(const uint32_t* buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] += buffer_a[i]*buffer_b[i];
    }


    template<typename T>
    void addProductC_nonIPP(T C, const T *buffer_a, const T *buffer_b, T *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer[i] = buffer_b[i] + buffer_a[i]*C;
    }

    template<typename T>
    void addProductC_nonIPP(T C, const T *buffer_in, T *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] += buffer_out[i] + buffer_in[i]*C;
    }

    void addProductC(double C, const double* buffer_a, const double *buffer_b, double *buffer, size_t length) {
        addProductC_nonIPP(C, buffer_a, buffer_b, buffer, length);
    }

    void addProductC(float C, const float* buffer_a, const float *buffer_b, float *buffer, size_t length) {
        copyBuffer(buffer_b, buffer, length);
        ippsAddProductC_32f(buffer_a, C, buffer, length);
    }

    void addProductC(int16_t C, const int16_t* buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) {
        addProductC_nonIPP(C, buffer_a, buffer_b, buffer, length);
    }

    void addProductC(int32_t C, const int32_t* buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) {
        addProductC_nonIPP(C, buffer_a, buffer_b, buffer, length);
    }

    void addProductC(uint16_t C, const uint16_t* buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) {
        addProductC_nonIPP(C, buffer_a, buffer_b, buffer, length);
    }

    void addProductC(uint32_t C, const uint32_t* buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) {
        addProductC_nonIPP(C, buffer_a, buffer_b, buffer, length);
    }

    void addProductC(double C, const double *buffer_in, double *buffer_out, size_t length) {
        addProductC_nonIPP(C, buffer_in, buffer_out, length);
    }

    void addProductC(float C, const float *buffer_in, float *buffer_out, size_t length) {
        ippsAddProductC_32f(buffer_in, C, buffer_out, length);
    }

    void addProductC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        addProductC_nonIPP(C, buffer_in, buffer_out, length);
    }

    void addProductC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        addProductC_nonIPP(C, buffer_in, buffer_out, length);
    }

    void addProductC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        addProductC_nonIPP(C, buffer_in, buffer_out, length);
    }

    void addProductC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        addProductC_nonIPP(C, buffer_in, buffer_out, length);
    }

    void abs(double *buffer,size_t length) {
        ippsAbs_64f_I(buffer, length);
    }

    void abs(float *buffer, size_t length) {
        ippsAbs_32f_I(buffer, length);
    }

    void abs(int16_t *buffer,size_t length) {
        ippsAbs_16s_I(buffer, length);
    }

    void abs(int32_t *buffer, size_t length) {
        ippsAbs_32s_I(buffer, length);
    }

    void abs(const double *buffer_in, double *buffer_out, size_t length) {
        ippsAbs_64f(buffer_in, buffer_out, length);
    }

    void abs(const float *buffer_in, float *buffer_out, size_t length) {
        ippsAbs_32f(buffer_in, buffer_out, length);
    }

    void abs(const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsAbs_16s(buffer_in, buffer_out, length);
    }

    void abs(const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        ippsAbs_32s(buffer_in, buffer_out, length);
    }

    void sqrt(double *buffer,size_t length) {
        ippsSqrt_64f_I(buffer, length);
    }

    void sqrt(float *buffer, size_t length) {
        ippsSqrt_32f_I(buffer, length);
    }

    void sqrt(int16_t *buffer,size_t length) {
        ippsSqrt_16s_ISfs(buffer, length, 0);
    }

    void sqrt(int32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer[i], buffer[i]);
    }

    void sqrt(uint32_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer[i], buffer[i]);
    }

    void sqrt(uint16_t *buffer, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer[i], buffer[i]);
    }

    void sqrt(const double *buffer_in, double *buffer_out, size_t length) {
        ippsSqrt_64f(buffer_in, buffer_out, length);
    }

    void sqrt(const float *buffer_in, float *buffer_out, size_t length) {
        ippsSqrt_32f(buffer_in, buffer_out, length);
    }

    void sqrt(const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsSqrt_16s_Sfs(buffer_in, buffer_out, length, 0);
    }

    void sqrt(const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer_in[i], buffer_out[i]);
    }

    void sqrt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer_in[i], buffer_out[i]);
    }

    void sqrt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            std_sqrt(buffer_in[i], buffer_out[i]);
    }

    template<typename T>
    void sqr_nonIPP(const T* buffer_in, T* buffer_out, size_t length) {
        for (size_t i = 0; i < length; ++i)
            buffer_out[i] = buffer_in[i]*buffer_in[i];
    }


    void sqr(double *buffer,size_t length) {
        ippsSqr_64f_I(buffer, length);
    }

    void sqr(float *buffer, size_t length) {
        ippsSqr_32f_I(buffer, length);
    }

    void sqr(int16_t *buffer,size_t length) {
        ippsSqr_16s_ISfs(buffer, length, 0);
    }

    void sqr(int32_t *buffer, size_t length) {
        sqr_nonIPP(buffer, buffer, length);
    }

    void sqr(uint32_t *buffer, size_t length) {
        sqr_nonIPP(buffer, buffer, length);
     }

    void sqr(uint16_t *buffer, size_t length) {
        sqr_nonIPP(buffer, buffer, length);
    }

    void sqr(const double *buffer_in, double *buffer_out, size_t length) {
        ippsSqr_64f(buffer_in, buffer_out, length);
    }

    void sqr(const float *buffer_in, float *buffer_out, size_t length) {
        ippsSqr_32f(buffer_in, buffer_out, length);
    }

    void sqr(const int16_t *buffer_in, int16_t *buffer_out, size_t length){
        ippsSqr_16s_Sfs(buffer_in, buffer_out, length, 0);
    }

    void sqr(const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        sqr_nonIPP(buffer_in, buffer_out, length);
    }

    void sqr(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        sqr_nonIPP(buffer_in, buffer_out, length);
    }

    void sqr(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        sqr_nonIPP(buffer_in, buffer_out, length);
    }

    void logn(double *buffer,size_t length) {
        ippsLn_64f_I(buffer, length);
    }

    void logn(float *buffer, size_t length) {
        ippsLn_32f_I(buffer, length);
    }

    void logn(int16_t *buffer,size_t length) {
        ippsLn_16s_ISfs(buffer, length, 0);
    }

    void logn(int32_t *buffer, size_t length) {
        ippsLn_32s_ISfs(buffer, length, 0);
    }

    void logn(uint32_t *buffer, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(buffer, intermediate_buffer, length);
        ippsLn_64f_I(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, buffer, length);
    }

    void logn(uint16_t *buffer, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(buffer, intermediate_buffer, length);
        ippsLn_64f_I(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, buffer, length);
    }

    void logn(const double *buffer_in, double *buffer_out, size_t length) {
        ippsLn_64f(buffer_in, buffer_out, length);
    }

    void logn(const float *buffer_in, float *buffer_out, size_t length) {
        ippsLn_32f(buffer_in, buffer_out, length);
    }

    void logn(const int16_t *buffer_in, int16_t *buffer_out, size_t length) {
        ippsLn_16s_Sfs(buffer_in, buffer_out, length, 0);
    }

    void logn(const int32_t *buffer_in, int32_t *buffer_out, size_t length) {
        ippsLn_32s_Sfs(buffer_in, buffer_out, length, 0);
    }

    void logn(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(buffer_in, intermediate_buffer, length);
        ippsLn_64f_I(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, buffer_out, length);
    }

    void logn(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(buffer_in, intermediate_buffer, length);
        ippsLn_64f_I(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, buffer_out, length);
    }

    void real2complex(const double *real, const double *imag, wipp_complex_t *complex, size_t length) {
        ippsRealToCplx_64f(real, imag, IPP64fc(complex), length);
    }

    void real(const wipp_complex_t *complex, double *real, size_t length) {
        ippsReal_64fc(cIPP64fc(complex), real, length);
    }

    void imag(const wipp_complex_t *complex, double *imag, size_t length) {
        ippsImag_64fc(cIPP64fc(complex), imag, length);
    }

    void conj(wipp_complex_t *complex, size_t length) {
        ippsConj_64fc_I(IPP64fc(complex), length);
    }

    void conj(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length) {
        ippsConj_64fc(cIPP64fc(complex_in), IPP64fc(complex_out), length);
    }

    void conjFlip(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length) {
        ippsConjFlip_64fc(cIPP64fc(complex_in), IPP64fc(complex_out), length);
    }

    void polar2cart(const double *module, const double *phase, wipp_complex_t *cart, size_t length) {
        ippsPolarToCart_64fc(module, phase, IPP64fc(cart), length);
    }

}

